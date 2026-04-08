#ifndef SHAPES
#define SHAPES


#include <iostream>
#include <vector>
#include "transform.hpp"

int S_VertexSize();

class S_Shape: public T_Transform{
    private:
    int vertexLength;
        std::vector<std::vector<double>> points;
        //a list of faces
        //faces are pointers to the index of a point in the points list
        std::vector<std::vector<double>> faces;      
        double Fov = M_PI/3;

    public:
        S_Shape(double x, double y, double z, double width, double height, double depth, double xAngle, double yAngle, double zAngle, std::vector<std::vector<double>> points, std::vector<std::vector<double>> faces);
        int GetVertexLength();
        std::vector<std::vector<double>> GetPoints();
        std::vector<std::vector<double>> GetFaces();

};
std::vector<S_Shape>* S_GetShapes();
int S_GetShapeSize();

#endif