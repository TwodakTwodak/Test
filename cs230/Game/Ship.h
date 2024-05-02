/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Sprite.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Seunghyeon Song
Created:    March 8, 2023
Updated:	March 23, 2024
*/

#ifndef SHIP_H
#define SHIP_H

#include "../Engine/Input.h"
#include "../Engine/Vec2.h"
#include "../Engine/GameObject.h"

#define DEGREES(x)          x * (PI / 180)

class Ship : public CS230::GameObject {
public:
    Ship(Math::vec2 start_position, double rotation, Math::vec2 scale);
    void Update(double dt) override;
    void Draw(Math::TransformationMatrix camera_matrix) override;

private:
    enum class Animations {
        None,
        Flaming
    };
    CS230::Sprite flame_left;
    CS230::Sprite flame_right;

    static constexpr double rotation_speed = DEGREES(180);
    static constexpr double speed = 700;
    static constexpr double drag = 1;
    static constexpr double scale = 0.75;
};

#endif 
