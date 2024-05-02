/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Matrix.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include "Vec2.h"

namespace Math {
    class TransformationMatrix {
    public:
        TransformationMatrix();

        const double* operator[](int index) const { return matrix[index]; }
        TransformationMatrix operator * (const TransformationMatrix& m) const;
        TransformationMatrix& operator *= (const TransformationMatrix& m);
        Math::vec3 operator*(const vec3& v) const;
        void Reset();
    protected:
        double matrix[4][4];
    };

    class TranslationMatrix : public TransformationMatrix {
    public:
        TranslationMatrix(const Math::vec3& translation);
        TranslationMatrix(const Math::ivec3& translation);
    };

    class ScaleMatrix : public TransformationMatrix {
    public:
        ScaleMatrix(double scale);
        ScaleMatrix(vec3 scale);
    };

    class RotationMatrix : public TransformationMatrix {
    public:
        RotationMatrix(double theta);
    };
}


