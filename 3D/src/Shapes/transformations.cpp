#include "transformations.hpp"
#include "transform.hpp"
#include "../Rendering/camera.hpp"
#include <vector>
#include <cmath>



std::vector<std::vector<double>> M_GetTranslationMatrix(T_Transform transform){ 
  std::vector<std::vector<double>> translationMatrix = {
      { 1, 0, 0 , transform.GetX()},
      { 0, 1, 0 , transform.GetY()},
      { 0, 0, 1 , transform.GetZ()},
      { 0, 0, 0 ,    1  }
    }; 
    return translationMatrix;
}

std::vector<std::vector<double>> M_GetScaleMatrix(T_Transform transform){ 
  std::vector<std::vector<double>> scaleMatrix = {
      { transform.GetWidth(),   0,        0 ,        0},
      { 0,         transform.GetHeight(), 0 ,        0},
      { 0,                 0, transform.GetDepth() , 0},
      { 0,                 0,         0 ,       1},
    };
  return scaleMatrix; 
}

std::vector<std::vector<double>> M_GetScaleAndTranslationMatrix(T_Transform transform){
  std::vector<std::vector<double>> scaleAndTranslationMatrix = {
      { transform.GetWidth(),   0,        0 ,        transform.GetX()},
      { 0,         transform.GetHeight(), 0 ,        transform.GetY()},
      { 0,                 0, transform.GetDepth() , transform.GetZ()},
      { 0,                 0,              0 ,               1       },
    };

  return scaleAndTranslationMatrix; 
}

std::vector<std::vector<double>> M_GetXAxisRotationMatrix(T_Transform transform){
  std::vector<std::vector<double>> xAxisRotationMatrix = {
      { 1,      0,                             0 ,                  0},
      { 0, cos(transform.GetXAngle()), -sin(transform.GetXAngle()), 0},
      { 0, sin(transform.GetXAngle()) , cos(transform.GetXAngle()), 0},
      { 0,       0,                           0 ,                   1}
    };

  return xAxisRotationMatrix; 
}
std::vector<std::vector<double>> M_GetYAxisRotationMatrix(T_Transform transform){
  std::vector<std::vector<double>> yAxisRotationMatrix = {
      { cos(transform.GetYAngle()),  0, sin(transform.GetYAngle()) ,0},
      {           0,            1,          0,            0},
      { -sin(transform.GetYAngle()), 0, cos(transform.GetYAngle()) ,0},
      {           0,            0,          0,            1}
    };

  return yAxisRotationMatrix; 
}
std::vector<std::vector<double>> M_GetZAxisRotationMatrix(T_Transform transform){
  std::vector<std::vector<double>> zAxisRotationMatrix = {
      { cos(transform.GetZAngle()), -sin(transform.GetZAngle()), 0 , 0},
      { sin(transform.GetZAngle()), cos(transform.GetZAngle()),  0 , 0},
      {           0,                      0,           1 , 0},
      {           0,                      0,           0 , 1}
    };

  return zAxisRotationMatrix; 
}

std::vector<std::vector<double>> M_GetClippingMatrix(double w){ 
  //std::cout<<"BlajSS"<<std::endl<<std::endl;
  double normalizedW = 1/w;
  std::cout<<std::endl;
  std::vector<std::vector<double>> translationMatrix = {
      { normalizedW, 0,      0 ,        0},
      { 0,      normalizedW, 0 ,        0},
      { 0,           0,   normalizedW , 0},
      { 0,           0,      0 ,   w}
    }; 
    std::cout<<std::endl;
    return translationMatrix;
}

std::vector<std::vector<double>> M_GetFOVMatrix(C_Camera camera){ 
  double near = camera.near;
  double far = camera.far;
  double top = near * tan(camera.vFov/2);
  double right = (16/9) * top;
  std::vector<std::vector<double>> translationMatrix = {
      { near/right,     0,               0 ,                       0},
      { 0,         near/top,            0 ,                        0},
      { 0,              0,    -(far+near)/(far-near) , -(2*far*near)/(far-near)},
      { 0,              0,               1 ,                        0}
    }; 
    return translationMatrix;
}

std::vector<std::vector<double>> M_GetViewPortMatrix(int screenWidth, int screenHeight){
  double width = screenWidth/2;
  double height = screenHeight/2;
  std::vector<std::vector<double>> GetViewPortMatrix = {
      { width, 0,    0 , width },
      { 0,   height, 0 , height},
      { 0,      0,   1 ,   0   },
      { 0,      0,   0 ,   1   }
    };

  return GetViewPortMatrix; 
}


//multiplies a 1 dementional vector and a multidementional vector
std::vector<double> M_MultiplyMatricies(std::vector<double> matrix1, std::vector<std::vector<double>> matrix2){
    std::vector<double> newMatrix = {};
    if(matrix1.size() != matrix2[0].size()){
      std::cout<<"These Cannot Be multiplied"<<std::endl;
      return {};                                                                                                                                                                                                                      
    }
    for(unsigned int i = 0; i < matrix2.size(); i++){
        double count = 0;
        for(unsigned int j = 0; j < matrix2[0].size(); j++){
            count += matrix2[i][j] * matrix1[j];
        }

        newMatrix.push_back(count);
    }
    return newMatrix;
}
//multiplies 2 matrixes of the same size
std::vector<std::vector<double>> M_MultiplyMatricies(std::vector<std::vector<double>> matrix1, std::vector<std::vector<double>> matrix2){
    std::vector<std::vector<double>> newMatrix = matrix2;
    if(matrix1[0].size() != matrix2.size()){
      return {};                                                                                                                                                                                                              
    }
    for (unsigned int i = 0; i < matrix1.size(); i++) {
        for (unsigned int j = 0; j < matrix2[0].size(); j++) {
            newMatrix[i][j] = 0;

            for (unsigned int k = 0; k < matrix2.size(); k++) {
                
                newMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
                
            }
        }
    }
    return newMatrix;
}