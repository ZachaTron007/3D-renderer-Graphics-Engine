#include "../Shapes/shapes.hpp"
#include "objects.hpp"
#include "../global.hpp"
#include "../Rendering/camera.hpp"
#include <cmath>

std::vector<std::vector<double>> cubePoints = 
   { {-1,  1, 1, 1}, //top front left
     { 1,  1, 1, 1}, //top front right
     {-1, -1, 1, 1}, //bottom front left
     { 1, -1, 1, 1}, //bottom front right

     {-1,  1, -1, 1}, //top back left
     { 1,  1, -1, 1}, //top back right
     {-1, -1, -1, 1}, //bottom back left
     { 1, -1, -1, 1} //top back right
   };

  std::vector<std::vector<double>> cubeFaces = 
   {  {0, 1, 3, 2},//Front Face
      {4, 5, 7, 6},//Back Face
      {0, 1, 5, 4},//Top Face
      {2, 3, 7, 6},//Bottom Face
      {1, 3, 7, 5},//Right Face
      {0, 2, 6, 4}//Left Face
   };

std::vector<std::vector<double>> pyramidPoints = 
 {  {0, 1, 0, 1},//Top
    {-1, -1, 1, 1},//Front Left
    {1, -1, 1, 1},//Front Right
    {1, -1, -1, 1},//Back Right
    {-1, -1, -1, 1},//Right Face
  };

std::vector<std::vector<double>> pyramidFaces = 
 {  {0, 1, 2},//Front
    {0, 3, 4},//Back
    {0, 1, 4},//Left
    {0, 2, 3},//Right
    {1, 2, 3, 4},//Bottom
  };

S_Shape* cube;
C_Camera* camera;

void O_GenerateObjects(){
    camera  = new C_Camera(
      -100.0,//x
      0.0,//y
      0.0,//z
      0.0,//width
      0.0,//height
      0.0,//depth
      0.0,//xAngle
      0.0,//M_PI/4,//yAngle
      0.0//zAngle
    );
    cube = new S_Shape(
      200,//x
      0,//y
      -500,//z
      100,//width
      50,//height
      50,//depth
      0,//xAngle
      0,//M_PI/4,//yAngle
      0,//zAngle
      cubePoints,//points
      cubeFaces//faces
    );
    cube->SetX(125);
    delete cube;
}

float moveSpeed = 100;
float rotateSpeed = 0.5;

void O_MoveSideways(int dir){
  //camera->SetY(camera->GetY() + G_GetDeltaTime() * dir * moveSpeed * sin(camera->GetXAngle() - M_PI/2));
  camera->SetX(camera->GetX() + G_GetDeltaTime() * dir * moveSpeed * -sin(camera->GetYAngle() - M_PI/2));
  camera->SetZ(camera->GetZ() + G_GetDeltaTime() * dir * moveSpeed * cos(camera->GetYAngle() - M_PI/2));
}

void O_MoveUp(int dir){
  camera->SetY(camera->GetY() + G_GetDeltaTime() * dir * moveSpeed * sin(camera->GetXAngle() + M_PI/2));
  //camera->SetX(camera->GetX() + G_GetDeltaTime() * dir * moveSpeed * -sin(camera->GetYAngle() - M_PI/2));
  camera->SetZ(camera->GetZ() + G_GetDeltaTime() * dir * moveSpeed * cos(camera->GetYAngle() + M_PI/2));
}

void O_MoveForward(int dir){
  camera->SetY(camera->GetY() + G_GetDeltaTime() * dir * moveSpeed * sin(camera->GetXAngle()));
  camera->SetX(camera->GetX() + G_GetDeltaTime() * dir * moveSpeed * -sin(camera->GetYAngle()));
  camera->SetZ(camera->GetZ() + G_GetDeltaTime() * dir * moveSpeed * cos(camera->GetYAngle()));
}

void O_MoveXAngle(int dir){
  camera->SetXAngle(camera->GetXAngle() + G_GetDeltaTime() * dir * rotateSpeed);
  //S_GetShapes()->at(0).SetXAngle(S_GetShapes()->at(0).GetXAngle() + G_GetDeltaTime() * dir * rotateSpeed);
}

void O_MoveYAngle(int dir){
  camera->SetYAngle(camera->GetYAngle() + G_GetDeltaTime() * dir * rotateSpeed);
  //S_GetShapes()->at(0).SetYAngle(S_GetShapes()->at(0).GetYAngle() + G_GetDeltaTime() * dir * rotateSpeed);
}

void O_MoveZAngle(int dir){
  S_GetShapes()->at(0).SetZAngle(S_GetShapes()->at(0).GetZAngle() + G_GetDeltaTime() * dir * rotateSpeed);
}