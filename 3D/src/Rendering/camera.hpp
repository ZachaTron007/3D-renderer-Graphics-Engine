#ifndef CAMERA_H
#define CAMERA_H
#include <vector>
#include "../Shapes/transform.hpp"
class C_Camera: public T_Transform{
    private:
        double hFov;
        //double vFov;
        //double near = 5;
        //double far = 10000;

    public:
    double near = 1;
    double far = 10000;
    double vFov;
    C_Camera(double x, double y, double z, double width, double height, double depth, double xAngle, double yAngle, double zAngle, double hFov);
    C_Camera(double x, double y, double z, double width, double height, double depth, double xAngle, double yAngle, double zAngle, double hFov, bool setAsMainCamera);
    C_Camera(double x, double y, double z, double width, double height, double depth, double xAngle, double yAngle, double zAngle, bool setAsMainCamera);
    C_Camera(double x, double y, double z, double width, double height, double depth, double xAngle, double yAngle, double zAngle);

    void SetAsMainCamera();
    void SetFOV(double fov);

};

#endif
