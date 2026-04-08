#include "camera.hpp"
#include "rendering.hpp"
#include <cmath>




C_Camera::C_Camera(double x, double y, double z, double width, double height, double depth, double xAngle, double yAngle, double zAngle): T_Transform(x, y, z, width, height, depth, xAngle, yAngle, zAngle){
    this-> vFov = M_PI/3;
    SetAsMainCamera();
}
C_Camera::C_Camera(double x, double y, double z, double width, double height, double depth, double xAngle, double yAngle, double zAngle, bool setAsMainCamera): T_Transform(x, y, z, width, height, depth, xAngle, yAngle, zAngle){
    this-> vFov = M_PI/3;
    if(setAsMainCamera) SetAsMainCamera();
}

C_Camera::C_Camera(double x, double y, double z, double width, double height, double depth, double xAngle, double yAngle, double zAngle, double hFov): T_Transform(x, y, z, width, height, depth, xAngle, yAngle, zAngle){
    this-> vFov = hFov;
    SetAsMainCamera();
}

C_Camera::C_Camera(double x, double y, double z, double width, double height, double depth, double xAngle, double yAngle, double zAngle, double hFov, bool setAsMainCamera): T_Transform(x, y, z, width, height, depth, xAngle, yAngle, zAngle){
    this-> vFov = hFov;
    if(setAsMainCamera) SetAsMainCamera();
}
//C_CAMERA::SetFOV(){}
void C_Camera::SetAsMainCamera(){ R_SetRenderCamera(this); }