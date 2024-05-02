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

class Robot : public CS230::GameObject {
public:
    Robot(Math::vec2 position);
};