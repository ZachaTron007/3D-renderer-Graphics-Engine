#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <iostream>
#include <vector>
#include "rendering.hpp"
#include "../Shapes/shapes.hpp"
#include "camera.hpp"
#include "../Shapes/transformations.hpp"
//#include "transformations.hpp"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
C_Camera* currentCamera;

void R_SetRenderCamera(C_Camera* camera){ currentCamera = camera; }

//720
const int screenWidth = 1280;
const int screenHeight = 720;

void ConvertToScreenSpace(double *x, double *y){
    *x *= screenWidth;
    *y *= screenHeight;
}
void ConvertToScreenSpaceAdd(double *x, double *y){
    *x += screenWidth;
    *y += screenHeight;
}

void DrawLine(float x0, float y0, float x1, float y1){
    float dx = x1 - x0;
    float dy = y1 - y0;
    float step = (abs(dx) > abs(dy))? abs(dx) : abs(dy);
    if(step !=0){
        float stepX = dx/step;

        float stepY = dy/step;
        for(int i = 0; i < step + 1; i++){
            int x = int(x0 + i *stepX + 0.5);
            int y = int(y0+ i *stepY + 0.5);
            SDL_RenderDrawPointF(renderer, x, y);
        }
    }
    
}
void FillShape(std::vector<double> face, std::vector<std::vector<double>> points){
    for(unsigned int i = 0; i < face.size(); i++){
        
        std::vector<double> point0 = points[face[i]];
        std::vector<double> point1 = points[face[(i+1)%face.size()]];
        //std::cout<< "Point 1: "<< face[i] << ", Point 2: "<< face[(i+1)%face.size()] <<std::endl;
        float dx = point1[0] - point0[0];
        float dy = point1[1] - point0[1];
        float step = (abs(dx) > abs(dy))? abs(dx) : abs(dy);
        if(step !=0){
            float stepX = dx/step;

            float stepY = dy/step;
            for(int i = 0; i < step + 1; i++){
                int x = int(point0[0] + i *stepX + 0.5);
                int y = int(point0[1]+ i *stepY + 0.5);
                SDL_RenderDrawPointF(renderer, x, y);
            }
        }
    }
    
}

void ConnectLinesSquare(std::vector<std::vector<double>> points){
    DrawLine(points[0][0], points[0][1], points[1][0], points[1][1]);
    DrawLine(points[0][0], points[0][1], points[2][0], points[2][1]);
    DrawLine(points[0][0], points[0][1], points[4][0], points[4][1]);

    DrawLine(points[1][0], points[1][1], points[5][0], points[5][1]);
    DrawLine(points[1][0], points[1][1], points[3][0], points[3][1]);

    DrawLine(points[2][0], points[2][1], points[3][0], points[3][1]);
    DrawLine(points[2][0], points[2][1], points[6][0], points[6][1]);

    DrawLine(points[3][0], points[3][1], points[7][0], points[7][1]);

    DrawLine(points[4][0], points[4][1], points[6][0], points[6][1]);
    DrawLine(points[4][0], points[4][1], points[5][0], points[5][1]);

    DrawLine(points[5][0], points[5][1], points[7][0], points[7][1]);

    DrawLine(points[6][0], points[6][1], points[7][0], points[7][1]);

}

std::vector<std::vector<double>> CacheWorldSpaceMatricies(S_Shape shape){
    std::vector<std::vector<double>> rotationMatrix = M_GetXAxisRotationMatrix(shape);
    rotationMatrix = M_MultiplyMatricies(M_GetYAxisRotationMatrix(shape), rotationMatrix);
    rotationMatrix = M_MultiplyMatricies(M_GetZAxisRotationMatrix(shape), rotationMatrix);
    rotationMatrix = M_MultiplyMatricies(M_GetScaleMatrix(shape),rotationMatrix);
    rotationMatrix = M_MultiplyMatricies(M_GetTranslationMatrix(shape),rotationMatrix);
    //std::vector<std::vector<double>> cameraMatrix = M_GetTranslationMatrix(camera);
    rotationMatrix = M_MultiplyMatricies(M_GetTranslationMatrix(*currentCamera), rotationMatrix);
    rotationMatrix = M_MultiplyMatricies(M_GetYAxisRotationMatrix(*currentCamera), rotationMatrix);
    rotationMatrix = M_MultiplyMatricies(M_GetXAxisRotationMatrix(*currentCamera), rotationMatrix);
    return rotationMatrix;
}

std::vector<std::vector<double>> CacheCameraMatricies(C_Camera camera){
    std::vector<std::vector<double>> cameraMatrix = M_GetTranslationMatrix(camera);
    cameraMatrix = M_MultiplyMatricies(M_GetYAxisRotationMatrix(camera), cameraMatrix);
    cameraMatrix = M_MultiplyMatricies(M_GetXAxisRotationMatrix(camera), cameraMatrix);
    return cameraMatrix;
}

std::vector<double> Transform(S_Shape currentShape, std::vector<double> points){
    std::vector<double> finishedPoints = points;
    //std::cout<<"Pre: "<<"x:, "<<finishedPoints[0]<<", y: "<<finishedPoints[1]<<", z: "<<finishedPoints[2]<<std::endl;
    
    finishedPoints[3]=finishedPoints[2];
    //std::cout<<"w: "<<finishedPoints[3]<<std::endl;
    finishedPoints = M_MultiplyMatricies(finishedPoints, M_GetFOVMatrix(*currentCamera));
    for(int i = 0; i < 4; i++) finishedPoints[i]/=finishedPoints[3];
    finishedPoints = M_MultiplyMatricies(finishedPoints, M_GetViewPortMatrix(screenWidth, screenHeight));
    //std::cout<<"w: "<<finishedPoints[3]<<std::endl;

    //std::cout<<"Post: "<<"x:, "<<finishedPoints[0]<<", y: "<<finishedPoints[1]<<", z: "<<finishedPoints[2]<<std::endl<<std::endl;
    return finishedPoints;
}


void R_RunDisplay(){
    
    //set background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    //draw Walls
    SDL_SetRenderDrawColor(renderer, 255, 150, 100, 0);
    std::vector<S_Shape>* shapes = S_GetShapes();
    //std::vector<std::vector<double>> cameraMatrix = CacheCameraMatricies(*currentCamera);
    //loops through all the shapes
    for(int i = 0; i < S_GetShapeSize(); i++){
        S_Shape currentShape = shapes->at(i);
        std::vector<std::vector<double>> points = currentShape.GetPoints();
        std::vector<std::vector<double>> matrix = CacheWorldSpaceMatricies(currentShape);
        //Loops through the verticies in the shape
        for(int j = 0; j < currentShape.GetVertexLength(); j++){
            std::vector<double> displayPoints = M_MultiplyMatricies(points[j], matrix);
            //isplayPoints = M_MultiplyMatricies(displayPoints, cameraMatrix);
            displayPoints = Transform(currentShape, displayPoints);

            SDL_RenderDrawPoint(renderer, displayPoints[0],displayPoints[1]);
            points[j] = displayPoints;
            
        }
        std::vector<std::vector<double>> faces = currentShape.GetFaces();
        for(unsigned int i = 0; i < faces.size(); i++){
            FillShape(faces[i],points);
        }
        //ConnectLinesSquare(points);
        
    }
    SDL_RenderPresent(renderer);
}

void R_StartDisplay(){
    //SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Test Window",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//Update the surface
}