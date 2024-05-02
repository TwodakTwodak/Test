/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Seunghyeon Song
Created:    March 8, 2023
Upadted:    March 14, 2024
*/

#include "../Engine/Engine.h"
#include "States.h"
#include "Mode1.h"
#include "Cat.h"
#include "Asteroid.h"
#include "Crates.h"
#include "Robot.h"
#include "Fonts.h"

Cat* cat_ptr = nullptr;

Mode1::Mode1() : camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.35 * Engine::GetWindow().GetSize().x, 0 } }) { }

void Mode1::Load() {
    //timer
    timer = timer_max;
    last_timer = static_cast<int>(timer_max);
    update_timer_text(last_timer);
    //?????? how could this point to garbage data?
    cat_ptr = new Cat({ 300, floor }, camera);
    gameobjectmanager.Add(cat_ptr);
    //asteroids
    gameobjectmanager.Add(new Asteroid({ 600, floor }));
    gameobjectmanager.Add(new Asteroid({ 1800, floor }));
    gameobjectmanager.Add(new Asteroid({ 2400, floor }));
    //crates
    gameobjectmanager.Add(new Crates({ 900, floor }, 2));
    gameobjectmanager.Add(new Crates({ 1400, floor }, 1));
    gameobjectmanager.Add(new Crates({ 2000, floor }, 5));
    gameobjectmanager.Add(new Crates({ 4000, floor }, 3));
    gameobjectmanager.Add(new Crates({ 5600, floor }, 5));
    //Robot
    gameobjectmanager.Add(new Robot({ 1200, Mode1::floor }));
    gameobjectmanager.Add(new Robot({ 2200, Mode1::floor }));
    gameobjectmanager.Add(new Robot({ 3400, Mode1::floor }));
    gameobjectmanager.Add(new Robot({ 4200, Mode1::floor }));
    backgrounds.Add("Assets/Planets.png", 0.25);
    backgrounds.Add("Assets/Ships.png", 0.5);
    backgrounds.Add("Assets/Foreground.png", 1);    
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ {0,0}, { backgrounds.GetSize() - Engine::GetWindow().GetSize() } });
    //what is the differnce between "Load("file", {})" and "Load("file")"
}

void Mode1::update_timer_text(int value) {
    timer_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Timer: " + std::to_string(value), 0xFFFFFFFF);
}

void Mode1::Update([[maybe_unused]] double dt) {
    gameobjectmanager.UpdateAll(dt);
    camera.Update(cat_ptr->GetPosition());

    timer -= dt;
    if (static_cast<int>(timer) < last_timer) {
        last_timer = static_cast<int>(timer);
        update_timer_text(last_timer);
    }
    if (last_timer == 0) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Main_menu));
    }else if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Main_menu));
    }
    //else if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
    //    Engine::GetGameStateManager().ReloadGameState();
    //}
    //whithout else if it could occur porblem
}

void Mode1::Draw() {
    Engine::GetWindow().Clear(0x000000FF);

    Math::TransformationMatrix camera_matrix = camera.GetMatrix();

    backgrounds.Draw(camera);
    gameobjectmanager.DrawAll(camera_matrix);

    timer_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x - 10 - timer_texture->GetSize().x, Engine::GetWindow().GetSize().y - timer_texture->GetSize().y - 5}));
    //Engine::GetLogger().LogDebug("Position: " + std::to_string(cat.GetPosition().x) + "    " + std::to_string(cat.GetPosition().y));
    //Draw part is wrong position is working well
}


void Mode1::Unload() {
    backgrounds.Unload();
    gameobjectmanager.Unload();
    cat_ptr = nullptr;
}




