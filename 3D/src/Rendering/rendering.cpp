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

//1080p
//const int screenWidth = 1920;
//const int screenHeight = 1080;

//1440p
//const int screenWidth = 2560;
//const int screenHeight = 1440;

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
std::vector<std::vector<double>> ClipPoints(std::vector<double> point1, std::vector<double> point2){
    
    std::vector<double> newPoint1 = point1;
    std::vector<double> newPoint2 = point2;
    //if undershoot
    float slope = (point2[1] - point1[1])/(point2[0] - point1[0]);
    float b1 = point1[1] - slope * point1[0];
    float b2 = point1[1] - slope * point1[0];
    //undershoot X
    //if(abs(slope) < 999999990){
        if(point1[0] < 0){
            //std::cout<<"slope: "<<slope<<", b: "<<b<<"\n";
                //std::cout<<point1[0]
            newPoint1[1] = b2;
         }
        if(point2[0] < 0){
            //std::cout<<"slope: "<<slope<<", b: "<<b<<"\n";
                //std::cout<<point1[0]
            newPoint2[1] = b1;
        }
    //}
        //overshoot X
    if(point1[0] > screenWidth){
        newPoint1[1] = slope * screenWidth + b2;
    }
    if(point2[0] > screenWidth){
        newPoint2[1] = slope * screenWidth + b1;
    }
    //if(abs(slope) > 0){
        if(point1[1] < 0){
            newPoint1[0] = -b2/slope;
        }
        if(point2[1] < 0){
            newPoint2[0] = -b1/slope;
        }
    //}
    if(point1[1] > screenHeight){
        newPoint1[0] = (screenHeight - b2)/slope;
    }
    if(point2[1] > screenHeight){
        newPoint2[0] = (screenHeight - b1)/slope;
    }
        
        return {newPoint1, newPoint2};

}

void FillShape(std::vector<double> face, std::vector<std::vector<double>> points){
    for(unsigned int i = 0; i < face.size(); i++){
        
        std::vector<std::vector<double>> pair = {points[face[i]], points[face[(i+1)%face.size()]]};
        pair = ClipPoints(pair[0], pair[1]);
        //std::cout<< "Point 1: "<< face[i] << ", Point 2: "<< face[(i+1)%face.size()] <<std::endl;
        double x0 = pair[0][0];
        double x1 = pair[1][0];
        double y0 = pair[0][1];
        double y1 = pair[1][1];
        
        float dx = x1 - x0; 
        float dy = y1 - y0;
        //Go Across the Outer edge
        float step = (abs(dx) > abs(dy))? abs(dx) : abs(dy);
        if(step !=0){
            float stepX = dx/step;

            float stepY = dy/step;
            for(int i = 0; i < step + 1; i++){
                    //get point on outter edge
                int x = int(x0 + i *stepX + 0.5);
                int y = int(y0+ i *stepY + 0.5);
                //if(point1[2] > 0 && point2[2] > 0)
                SDL_RenderDrawPointF(renderer, x, y);
                //shoot downwards
                /*for(int j = 0; j < 100; j++){
                    //int x1 = int(x + i *stepY + 0.5);
                    //int newY = int(y+ i *stepX + 0.5);
                    SDL_RenderDrawPointF(renderer, x, y+j);
                }*/
            }
        }
    }

    
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
    
    finishedPoints = M_MultiplyMatricies(finishedPoints, M_GetFOVMatrix(*currentCamera));
    if(finishedPoints[3]>0.00001){
        for(int i = 0; i < 4; i++) {
            finishedPoints[i]/=finishedPoints[3];
            
        }
    }
    finishedPoints = M_MultiplyMatricies(finishedPoints, M_GetViewPortMatrix(screenWidth, screenHeight));
    //std::cout<<"z: "<<finishedPoints[2]<<std::endl;

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