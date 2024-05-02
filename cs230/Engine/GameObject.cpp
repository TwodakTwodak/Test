/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObject.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "GameObject.h"

CS230::GameObject::GameObject() :
    GameObject({0,0}, 0, { 1, 1 })
{
}

CS230::GameObject::GameObject(Math::vec3 position) :
    GameObject(position, 0, { 1, 1 })
{}

CS230::GameObject::GameObject(Math::vec3 position, double rotation, Math::vec3 scale) :
    velocity({ 0,0 }),
    position(position),
    scale(scale),
    rotation(rotation),
    current_state(&state_none)
{}

void CS230::GameObject::Update(double dt) {
    current_state->Update(this, dt);
    sprite.Update(dt);
    if (velocity.x != 0 || velocity.y != 0) {
        UpdatePosition(velocity * dt);
    }
    current_state->CheckExit(this);
}

void CS230::GameObject::change_state(State* new_state) {
    current_state = new_state;
    current_state->Enter(this);
}

void CS230::GameObject::Draw(Math::TransformationMatrix camera_matrix) {
    sprite.Draw(camera_matrix * GetMatrix());
}

const Math::TransformationMatrix& CS230::GameObject::GetMatrix() {
    if (!matrix_outdated) {
        object_matrix = Math::TranslationMatrix(position) * Math::RotationMatrix(rotation) * Math::ScaleMatrix(scale);
        matrix_outdated = true;
    }
    return object_matrix;
}

const Math::vec3& CS230::GameObject::GetPosition() const
{
    return position;
}

const Math::vec3& CS230::GameObject::GetVelocity() const
{
    return velocity;
}

const Math::vec3& CS230::GameObject::GetScale() const
{
    return scale;
}

double CS230::GameObject::GetRotation() const
{
    return rotation;
}

void CS230::GameObject::SetPosition(Math::vec3 new_position) {
    matrix_outdated = false;
    position = new_position;
}

void CS230::GameObject::UpdatePosition(Math::vec3 delta) {
    matrix_outdated = false;
    position += delta;
}

void CS230::GameObject::SetVelocity(Math::vec3 new_velocity)
{
    matrix_outdated = false;
    velocity = new_velocity;
}

void CS230::GameObject::UpdateVelocity(Math::vec3 delta)
{
    matrix_outdated = false;
    velocity += delta;
}

void CS230::GameObject::SetScale(Math::vec3 new_scale)
{
    matrix_outdated = false;
    scale = new_scale;
}

void CS230::GameObject::UpdateScale(Math::vec3 delta)
{
    matrix_outdated = false;
    scale += delta;
}

void CS230::GameObject::SetRotation(double new_rotation)
{
    matrix_outdated = false;
    rotation = new_rotation;
}

void CS230::GameObject::UpdateRotation(double delta)
{
    matrix_outdated = false;
    rotation += delta;
}
