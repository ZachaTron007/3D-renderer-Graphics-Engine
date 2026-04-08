#include "shapes.hpp"
#include "transform.hpp"
#include <vector>
#include <iostream>

//cord lenght
const int VERTEX_SIZE = 4;
int S_GetVertexSize(){ return VERTEX_SIZE; }

//shape list info
std::vector<S_Shape> shapes = {};
std::vector<S_Shape>* S_GetShapes(){ return &shapes; }
int S_GetShapeSize(){ return shapes.size(); }

//shape inittilization
//ANGLES ARE IN RADIANS
S_Shape::S_Shape(double x, double y, double z, double width, double height, double depth, double xAngle, double yAngle, double zAngle, std::vector<std::vector<double>> points, std::vector<std::vector<double>> faces): T_Transform(x, y, z, width, height, depth, xAngle, yAngle, zAngle){
    this->points = points;
    this->faces = faces;
    vertexLength = points.size();
    shapes.push_back(*this);
    
}

//shape getting and setting
int S_Shape::GetVertexLength(){ return vertexLength; }
std::vector<std::vector<double>> S_Shape::GetPoints(){ return points; };
std::vector<std::vector<double>> S_Shape::GetFaces(){ return faces; };




