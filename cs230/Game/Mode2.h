/*
Copyright (C) 2024 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode2.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Seunghyeon Song
Created:    March 15, 2024
*/

#ifndef Mode2_H
#define Mode2_H

#include "../Engine/GameState.h"
#include "../Engine/GameObjectManager.h"

class Mode2 : public CS230::GameState {
public:
    Mode2();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "Mode2";
    }

private:
    CS230::GameObjectManager gameobjectmanager;
};


#endif