/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Robot.cpp
Project:    CS230 Engine
Author:     Seunghyeon Song
Created:    April 23, 2024
*/

#include "Meteor.h"
#include "../Engine/Engine.h"

Meteor::Meteor(Math::ivec2 window) {
	sprite.Load("Assets/Meteor.spt");
	SetVelocity({ -default_velocity + ((double)rand() / (double)RAND_MAX) * default_velocity * 2 , -default_velocity + ((double)rand() / (double)RAND_MAX) * default_velocity * 2 });
	//SetRotation((rand() / RAND_MAX) * 2 * PI * (PI / 180));
    SetRotation(((double)rand() / (double)RAND_MAX) * 2 * PI);
    SetPosition({ ((double)rand() / (double)RAND_MAX) * (double)window.x, ((double)rand() / (double)RAND_MAX) * (double)window.y });
    //(float)RAND_MAX has difference with jus RAND_MAX if we dont use this it will only int 0 - 1 but double make 0.1 0.32
    //Seems impossible to get window size here beacuse not setted yet!
    Engine::GetLogger().LogDebug("Velocity: " + std::to_string(GetVelocity().x) + ", " + std::to_string(GetVelocity().y));
    Engine::GetLogger().LogDebug("Position: " + std::to_string(GetPosition().x) + ", " + std::to_string(GetPosition().y));
    Engine::GetLogger().LogDebug("Rotation: " + std::to_string(GetRotation()));
}

void Meteor::Update(double dt)
{
    Math::vec2 temp_velocity = GetVelocity();
    UpdatePosition(temp_velocity * dt);
    //????? why can i calculate this

    if (GetPosition().x < -sprite.GetFrameSize().x - 5) {
        SetPosition({ Engine::GetWindow().GetSize().x + (double)(sprite.GetFrameSize().x) , GetPosition().y });
    }
    else if (GetPosition().x > Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x + 5) {
        SetPosition({ (double)(-sprite.GetFrameSize().x) , GetPosition().y });
    }

    if (GetPosition().y < -sprite.GetFrameSize().y - 5) {
        SetPosition({ GetPosition().x , Engine::GetWindow().GetSize().y + (double)(sprite.GetFrameSize().y) });
    }
    else if (GetPosition().y > Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y + 5) {
        SetPosition({ GetPosition().x , (double)(-sprite.GetFrameSize().y) });
    }
}

