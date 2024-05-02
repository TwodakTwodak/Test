/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Cat.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#ifndef CAT_H
#define CAT_H

#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/GameObject.h"

class Cat : public CS230::GameObject {
public:
    Cat(Math::vec2 start_position, const CS230::Camera& camera);
    void Update(double dt) override;
    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }

private:
    enum class Animations {
        Idle,
        Running,
        Jumping,
        Falling,
        Skidding
    };

    //could replace with key released?
    //but it could be more complicate?

    static constexpr double x_acceleration = 400;
    static constexpr double x_drag = 450;
    static constexpr double max_velocity = 400;
    static constexpr double jump_velocity = 650;

    const CS230::Camera& camera;
    //static constexpr double this fomat need's deafult value!!

    void update_x_velocity(double dt);

    //Idle
    class State_Idle : public State {
    public:
        virtual void Enter(GameObject* cat) override;
        virtual void Update(GameObject* cat, double dt) override;
        virtual void CheckExit(GameObject* cat) override;
        std::string GetName() override { return "Idle"; }
    };

    State_Idle state_idle;

    //Jump
    class State_Jumping : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };

    State_Jumping state_jumping;

    //Fall
    class State_Falling : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Falling"; }
    };

    State_Falling state_falling;

    //Run
    class State_Running : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Running"; }
    };

    State_Running state_running;

    //Skid
    class State_Skidding : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Skidding"; }
    };

    State_Skidding state_skidding;
};

#endif
