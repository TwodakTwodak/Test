/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Main_menu.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once

#include "../Engine/GameState.h"
#include "../Engine/Texture.h"


enum Button{
    Side_Scroller,
    Space_Shooter,
    Exit,
    Size
};

class Main_menu : public CS230::GameState {
public:
    Main_menu();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "Main_menu";
    }

private:

    CS230::Texture* title;
    CS230::Texture* buttons[Size];
    //no resaon for this
    std::string strings[Size];
    int current_button;

};

