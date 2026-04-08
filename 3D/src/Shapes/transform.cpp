#include "transform.hpp"
#include <vector>
#include <iostream>

//Transform inittilization
//ANGLES ARE IN RADIANS
T_Transform::T_Transform(double x, double y, double z, double width, double height, double depth, double xAngle, double yAngle, double zAngle){
    this->x = x;
    this->y = y;
    this->z = z;
    this->width = width;
    this->height = height;
    this->depth = depth;
    this->xAngle = xAngle;
    this->yAngle = yAngle;
    this->zAngle = zAngle;
}

//shape getting and setting
double T_Transform::GetX(){ return x; }
double T_Transform::GetY(){ return y; }
double T_Transform::GetZ(){ return z; }
void T_Transform::SetX(double x){ this->x = x; }
void T_Transform::SetY(double y){ this->y = y; }
void T_Transform::SetZ(double z){ this->z = z; }

double T_Transform::GetXAngle(){ return xAngle; }
double T_Transform::GetYAngle(){ return yAngle; }
double T_Transform::GetZAngle(){ return zAngle; }
void T_Transform::SetXAngle(double xAngle){ this->xAngle = xAngle; }
void T_Transform::SetYAngle(double yAngle){ this->yAngle = yAngle; }
void T_Transform::SetZAngle(double zAngle){ this->zAngle = zAngle; }

double T_Transform::GetWidth(){ return width; }
double T_Transform::GetHeight(){ return height; }
double T_Transform::GetDepth(){ return depth; }
void T_Transform::SetWidth(double width){ this->width = width; }
void T_Transform::SetHeight(double height){ this->height = height; }
void T_Transform::SetDepth(double depth){ this->depth = depth; }



