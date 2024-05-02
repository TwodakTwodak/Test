/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Camera.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "Camera.h"



CS230::Camera::Camera(Math::rect player_zone) : player_zone(player_zone){
}

void CS230::Camera::SetPosition(Math::vec3 new_position){
    position = new_position;
}

const Math::vec3& CS230::Camera::GetPosition() const{
    return position;
}

void CS230::Camera::SetLimit(Math::irect new_limit){
    limit = new_limit;
}

void CS230::Camera::Update(const Math::vec3& player_position) {
    if (player_position.x > player_zone.top_right.x + position.x) {
        position.x = player_position.x - player_zone.top_right.x;
    }
    if (player_position.x - position.x < player_zone.bottom_left.x) {
        position.x = player_position.x - player_zone.bottom_left.x;
    }
    //this two move camera position

    if (position.x < limit.bottom_left.x) {
        position.x = limit.bottom_left.x;
    }
    if (position.x > limit.top_right.x) {
        position.x = limit.top_right.x;
    }
    if (position.y < limit.bottom_left.y) {
        position.y = limit.bottom_left.y;
    }
    if (position.y > limit.top_right.y) {
        position.y = limit.top_right.y;
    }
    //this restrict camera position
}

Math::TransformationMatrix CS230::Camera::GetMatrix() {
    return Math::TranslationMatrix(-position);
}
