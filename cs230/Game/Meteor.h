/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Robot.h
Project:    CS230 Engine
Author:     Seunghyeon Song
Created:    April 23, 2024
*/

#pragma once
#include "../Engine/GameObject.h"

class Meteor : public CS230::GameObject {
public:
    Meteor(Math::ivec2 window);
    void Update(double dt) override;
private:
    static constexpr double default_velocity = 100;
};