/*
Copyright (C) 2024 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Seunghyeon Song
Created:    March 15, 2024
*/

#ifndef Mode1_H
#define Mode1_H

#include "../Engine/GameState.h"
#include "../Engine/GameObjectManager.h"
#include "Background.h"

class Mode1 : public CS230::GameState {
public:
    Mode1();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "Mode1";
    }

    static constexpr double gravity = 800;
    static constexpr double floor = 80;
    static constexpr double timer_max = 30;

private:
    Background backgrounds;
    CS230::GameObjectManager gameobjectmanager;
    CS230::Camera camera;
    CS230::Texture* timer_texture;
    //?????
    double timer;
    int last_timer;
    void update_timer_text(int value);
};


#endif