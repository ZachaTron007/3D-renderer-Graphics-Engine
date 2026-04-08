#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <vector>
#include "transform.hpp"
#include "../Rendering/camera.hpp"

std::vector<std::vector<double>> M_GetTranslationMatrix(T_Transform transform);
std::vector<std::vector<double>> M_GetScaleMatrix(T_Transform transform);
std::vector<std::vector<double>> M_GetScaleAndTranslationMatrix(T_Transform transform);

std::vector<std::vector<double>> M_GetXAxisRotationMatrix(T_Transform transform);
std::vector<std::vector<double>> M_GetYAxisRotationMatrix(T_Transform transform);
std::vector<std::vector<double>> M_GetZAxisRotationMatrix(T_Transform transform);

std::vector<std::vector<double>> M_GetClippingMatrix(T_Transform transform);
std::vector<std::vector<double>> M_GetFOVMatrix(C_Camera camera);
std::vector<std::vector<double>> M_GetViewPortMatrix(int screenWidth, int screenHeight);

std::vector<std::vector<double>> M_MultiplyMatricies(std::vector<std::vector<double>> matrix1, std::vector<std::vector<double>> matrix2);
std::vector<double> M_MultiplyMatricies(std::vector<double> matrix1, std::vector<std::vector<double>> matrix2);

#endif