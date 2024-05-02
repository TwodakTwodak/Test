/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Background.h
Project:    CS230 Engine
Author:     Jonathan Holmes, Seunghyeon Song
Created:    March 8, 2023
Updated:	March 30, 2024
*/

#include "Background.h"
#include "../Engine/Engine.h"
void Background::Add(const std::filesystem::path& texture_path, double speed)
{
	backgrounds.push_back({ Engine::GetTextureManager().Load(texture_path) , speed});
}

void Background::Unload()
{
}

void Background::Draw(const CS230::Camera& camera)
{
	for (ParallaxLayer background : backgrounds) {
		background.texture->Draw(Math::TranslationMatrix(Math::vec2({ 0 - (camera.GetPosition().x * background.speed), 0 - camera.GetPosition().y })));
	}
}

Math::ivec2 Background::GetSize()
{
	return backgrounds[backgrounds.size() - 1].texture->GetSize();
	//not sure
}
