/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Cat.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "Cat.h"
#include "../Engine/Engine.h"
#include "Mode1.h"

Cat::Cat(Math::vec2 start_position, const CS230::Camera& camera) :
    GameObject(start_position),
    camera(camera)
{
    current_state = &state_idle;
    sprite.Load("Assets/Cat.spt");
    current_state->Enter(this);
}

void Cat::update_x_velocity(double dt) {
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        UpdateVelocity({ x_acceleration * dt , 0 });
        if (GetVelocity().x > max_velocity) {
            SetVelocity({ max_velocity , GetVelocity().y});
        }
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
        UpdateVelocity({ -x_acceleration * dt , 0 });
        if (GetVelocity().x < -max_velocity) {
            SetVelocity({ -max_velocity , GetVelocity().y });
        }
    }
    else {
        if (GetVelocity().x > x_drag * dt) {
            UpdateVelocity({ -x_drag * dt , 0 });
        }
        else if (GetVelocity().x < -x_drag * dt) {
            UpdateVelocity({ x_drag * dt , 0 });
        }
        else {
            SetVelocity({ 0 , GetVelocity().y });
        }
    }
}

//Idle
void Cat::State_Idle::Enter(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    cat->sprite.PlayAnimation(static_cast<int>(Animations::Idle));
}
void Cat::State_Idle::Update(GameObject* object, double dt) { }
void Cat::State_Idle::CheckExit(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
        cat->change_state(&cat->state_running);
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        cat->change_state(&cat->state_running);
    }
    else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)) {
        cat->change_state(&cat->state_jumping);
    }
}

//Jump
void Cat::State_Jumping::Enter(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    cat->sprite.PlayAnimation(static_cast<int>(Animations::Jumping));
    cat->SetVelocity({ cat->GetVelocity().x , Cat::jump_velocity });
}
void Cat::State_Jumping::Update(GameObject* object, double dt) {
    Cat* cat = static_cast<Cat*>(object);
    cat->UpdateVelocity({0 , -Mode1::gravity * dt });
    cat->update_x_velocity(dt);
}
void Cat::State_Jumping::CheckExit(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Up) == false) {
        cat->change_state(&cat->state_falling);
        cat->SetVelocity({cat->GetVelocity().x, 0});
    }
    else if (cat->GetVelocity().y <= 0) {
        cat->change_state(&cat->state_falling);
    }
}

//Fall
void Cat::State_Falling::Enter(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    cat->sprite.PlayAnimation(static_cast<int>(Animations::Falling));
}
void Cat::State_Falling::Update(GameObject* object, double dt) {
    Cat* cat = static_cast<Cat*>(object);
    cat->UpdateVelocity({ 0 , -Mode1::gravity * dt });
    cat->update_x_velocity(dt);
}
void Cat::State_Falling::CheckExit(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    if (cat->GetPosition().y <= Mode1::floor) {
        cat->SetVelocity({ cat->GetVelocity().x, 0 });
        cat->SetPosition({ cat->GetPosition().x, Mode1::floor });
        cat->change_state(&cat->state_running);
    }
}

//Run
void Cat::State_Running::Enter(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    cat->sprite.PlayAnimation(static_cast<int>(Animations::Running));
}
void Cat::State_Running::Update(GameObject* object, double dt) {
    Cat* cat = static_cast<Cat*>(object);
    cat->update_x_velocity(dt);
}
void Cat::State_Running::CheckExit(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    if (cat->GetVelocity().x == 0) {
        cat->change_state(&cat->state_idle);
    }else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Up)) {
        cat->change_state(&cat->state_jumping);
    }else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left) && cat->GetScale().x >= 0.5) {
        cat->change_state(&cat->state_skidding);
    }else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right) && cat->GetScale().x <= -0.5) {
        cat->change_state(&cat->state_skidding);
    }
}

//Skid
void Cat::State_Skidding::Enter(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    cat->sprite.PlayAnimation(static_cast<int>(Animations::Skidding));
}
void Cat::State_Skidding::Update(GameObject* object, double dt) {
    Cat* cat = static_cast<Cat*>(object);
    if (cat->GetVelocity().x > 0) {
        cat->UpdateVelocity({ -((x_drag + x_acceleration) * dt) , 0});
    }
    else if (cat->GetVelocity().x < 0) {
        cat->UpdateVelocity({ (x_drag + x_acceleration) * dt , 0 });
    }
}
void Cat::State_Skidding::CheckExit(GameObject* object) {
    Cat* cat = static_cast<Cat*>(object);
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Up)) {
        cat->change_state(&cat->state_jumping);
    }else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left) && cat->GetVelocity().x <= 0) {
        cat->SetScale({ -1, 1 });
        cat->change_state(&cat->state_running);
    }else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right) && cat->GetVelocity().x >= 0) {
        cat->SetScale({ 1, 1 });
        cat->change_state(&cat->state_running);
    }
}
//

//Upadte
void Cat::Update(double dt) {
    GameObject::Update(dt);
    // Boundary Check
    if (GetPosition().x < camera.GetPosition().x + sprite.GetFrameSize().x / 2) {
        SetPosition({ camera.GetPosition().x + sprite.GetFrameSize().x / 2, GetPosition().y });
        SetVelocity({ 0, GetVelocity().y });
    }
    if (GetPosition().x + sprite.GetFrameSize().x / 2 > camera.GetPosition().x + Engine::GetWindow().GetSize().x) {
        SetPosition({ camera.GetPosition().x + Engine::GetWindow().GetSize().x - sprite.GetFrameSize().x / 2, GetPosition().y });
        SetVelocity({ 0, GetVelocity().y });
    }
}


//some space exist! beacuse of tail??