/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Camera.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix.h"
#include "Rect.h"

namespace CS230 {
    class Camera {
    public:
        Camera(Math::rect player_zone);
        void SetPosition(Math::vec3 new_position);
        const Math::vec3& GetPosition() const;
        void SetLimit(Math::irect new_limit);
        void Update(const Math::vec3& player_position);
        Math::TransformationMatrix GetMatrix();
    private:
        Math::irect limit;
        Math::vec3 position;
        Math::rect player_zone;
    };
}

#endif
