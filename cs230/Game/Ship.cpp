/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Ship.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Seunghyeon Song
Created:    March 8, 2023
Updated:	March 23, 2024
*/

#include "Ship.h"
#include "../Engine/Engine.h"

Ship::Ship(Math::vec2 start_position, double rotation, Math::vec2 scale) :
    GameObject(start_position, rotation, scale)
{
    sprite.Load("Assets/Ship.spt");
    flame_left.Load("Assets/Flame.spt");
    flame_right.Load("Assets/Flame.spt");
    flame_left.PlayAnimation(static_cast<int>(Animations::None));
    flame_right.PlayAnimation(static_cast<int>(Animations::None));
}

void Ship::Update(double dt) {
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)) {
        flame_left.PlayAnimation(static_cast<int>(Animations::Flaming));
        flame_right.PlayAnimation(static_cast<int>(Animations::Flaming));
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) {
        UpdateVelocity(Math::RotationMatrix(GetRotation()) * Math::vec2{ 0, speed * dt });
    }
    else {
        flame_left.PlayAnimation(static_cast<int>(Animations::None));
        flame_right.PlayAnimation(static_cast<int>(Animations::None));
    }

    if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        UpdateRotation(rotation_speed * dt);
    }

    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        UpdateRotation(-(rotation_speed * dt));
    }

    Math::vec2 temp_velocity = GetVelocity();
    UpdateVelocity(-temp_velocity * drag * dt);

    Engine::GetLogger().LogDebug("Velocity: " + std::to_string(GetVelocity().x) + ", " + std::to_string(GetVelocity().y));

    flame_left.Update(dt);
    flame_right.Update(dt);
    UpdatePosition(temp_velocity * dt);
    //might occur error

    //Test for wrap, here
    if (GetPosition().x < -sprite.GetFrameSize().x - 5) {
        SetPosition({ Engine::GetWindow().GetSize().x + (double)(sprite.GetFrameSize().x) , GetPosition().y });
    }
    else if (GetPosition().x > Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x + 5) {
        SetPosition({ (double)(-sprite.GetFrameSize().x) , GetPosition().y });
    }

    if (GetPosition().y < -sprite.GetFrameSize().y - 5) {
        SetPosition({ GetPosition().x , Engine::GetWindow().GetSize().y + (double)(sprite.GetFrameSize().y) });
    }else if (GetPosition().y > Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y + 5) {
        SetPosition({ GetPosition().x , (double)(- sprite.GetFrameSize().y)});
    }
    //Isn't it not efficent GetTextureSize() every single time?
    //Could made variable at outside
    //But if we will change size of Texture it could occurr error!!
    //It will be good to make local variable
}


void Ship::Draw(Math::TransformationMatrix camera_matrix) {
    sprite.Draw(camera_matrix * GetMatrix());
    flame_left.Draw(camera_matrix * GetMatrix() * Math::TranslationMatrix(sprite.GetHotSpot(1)));
    flame_right.Draw(camera_matrix * GetMatrix() * Math::TranslationMatrix(sprite.GetHotSpot(2)));
}
