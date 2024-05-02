/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Matrix.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Jiyun Seok
Created:    March 8, 2023
*/#include "Matrix.h"
#include <cmath>

using namespace Math;

TransformationMatrix::TransformationMatrix() {
    Reset();
}

void TransformationMatrix::Reset() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

TransformationMatrix TransformationMatrix::operator * (const TransformationMatrix& m) const {
    TransformationMatrix result;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.matrix[i][j] = matrix[i][0] * m.matrix[0][j] +
                matrix[i][1] * m.matrix[1][j] +
                matrix[i][2] * m.matrix[2][j] +
                matrix[i][3] * m.matrix[3][j];
        }
    }

    return result;
}

TransformationMatrix& TransformationMatrix::operator *= (const TransformationMatrix& m) {
    (*this) = (*this) * m;
    return (*this);
}

vec3 TransformationMatrix::operator * (const vec3& v) const {
    vec3 result;
    result.x = matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2] * v.z + matrix[0][3];
    result.y = matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2] * v.z + matrix[1][3];
    result.z = matrix[2][0] * v.x + matrix[2][1] * v.y + matrix[2][2] * v.z + matrix[2][3];
    return result;
}

TranslationMatrix::TranslationMatrix(const vec3& translation) {
    matrix[0][3] = translation.x;
    matrix[1][3] = translation.y;
    matrix[2][3] = translation.z;
}

TranslationMatrix::TranslationMatrix(const ivec3& translation) {
    matrix[0][3] = static_cast<double>(translation.x);
    matrix[1][3] = static_cast<double>(translation.y);
    matrix[2][3] = static_cast<double>(translation.z);
}

ScaleMatrix::ScaleMatrix(double scale) {
    matrix[0][0] = scale;
    matrix[1][1] = scale;
    matrix[2][2] = scale;
}

ScaleMatrix::ScaleMatrix(vec3 scale) {
    matrix[0][0] = scale.x;
    matrix[1][1] = scale.y;
    matrix[2][2] = scale.z;
}

RotationMatrix::RotationMatrix(double theta) {
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);

    matrix[0][0] = cosTheta;
    matrix[0][1] = -sinTheta;
    matrix[1][0] = sinTheta;
    matrix[1][1] = cosTheta;
}
