/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode2.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "../Engine/Engine.h"
#include "States.h"
#include "Ship.h"
#include "Meteor.h"
#include "Mode2.h"


//(Math::vec2)(Engine::GetWindow().GetSize()/2)
//maybe seqeucne of main cpp ? we should update widnow first!
Mode2::Mode2() { }

void Mode2::Load() {
    gameobjectmanager.Add(new Ship((Math::vec2)(Engine::GetWindow().GetSize() / 2), 0.0 , { 0.75, 0.75 }));
    for (int i = 0; i < 5; ++i) {
        gameobjectmanager.Add(new Meteor(Engine::GetWindow().GetSize()));
    }
}

void Mode2::Update([[maybe_unused]] double dt) {
    gameobjectmanager.UpdateAll(dt);
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Escape)) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Main_menu));
    }
    //if (Engine::GetInput().KeyDown(CS230::Input::Keys::Two)) {
    //    Engine::GetGameStateManager().ClearNextGameState();
    //}else if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
    //    Engine::GetGameStateManager().ReloadGameState();
    //}
    //not sure about this sequence of code is very important!
}

void Mode2::Draw() {
    Engine::GetWindow().Clear(0x000000FF);
    gameobjectmanager.DrawAll(Math::TransformationMatrix());
}

void Mode2::Unload() {
    //intersting part!!
    gameobjectmanager.Unload();
}



