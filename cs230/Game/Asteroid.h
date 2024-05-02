/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Asteroid.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#ifndef ASTEROID_H
#define ASTEROID_H

#include "../Engine/GameObject.h"

class Asteroid : public CS230::GameObject {
public:
    Asteroid(Math::vec2 start_position);

private:
    enum class Animations {
        Landing,
        Bouncing
    };

    static constexpr double bounce_velocity = 500;

    //Bounce
    class State_Bouncing : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Bouncing"; }
    };

    State_Bouncing state_bouncing;

    //Land
    class State_Landing : public State {
    public:
        virtual void Enter(GameObject* asteroid) override;
        virtual void Update(GameObject* asteroid, double dt) override;
        virtual void CheckExit(GameObject* asteroid) override;
        std::string GetName() override { return "Landing"; }
    };

    State_Landing state_landing;
};

#endif