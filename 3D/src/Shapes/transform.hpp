#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <iostream>
#include <vector>
#include <cmath>

int S_VertexSize();

class T_Transform{
    private:
        double x;
        double y;
        double z;
        double width;
        double height;
        double depth;
        double xAngle;
        double yAngle;
        double zAngle;

    public:
        T_Transform(double x, double y, double z, double width, double height, double depth, double xAngle, double yAngle, double zAngle);

        double GetX();
        double GetY();
        double GetZ();
        void SetX(double x);
        void SetY(double x);
        void SetZ(double z);
        void SetPoint(std::vector<double> point);

        double GetXAngle();
        double GetYAngle();
        double GetZAngle();
        void SetXAngle(double xAngle);
        void SetYAngle(double yAngle);
        void SetZAngle(double zAngle);
        

        double GetWidth();
        double GetHeight();
        double GetDepth();
        void SetWidth(double width);
        void SetHeight(double height);
        void SetDepth(double depth);

};

#endif