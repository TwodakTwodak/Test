/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Sprite.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include <string>
#include "Vec2.h"
#include "Matrix.h"
#include "Texture.h"
#include "Animation.h"

namespace CS230 {
    class Sprite {
    public:
        Sprite();
        ~Sprite();
        //this thing make problem when i use push_back at asteroids!! because of deleteing sprite thing

        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;

        Sprite(Sprite&& temporary) noexcept;
        Sprite& operator=(Sprite&& temporary) noexcept;

        void Update(double dt);
        void Load(const std::filesystem::path& sprite_file);
        void Draw(Math::TransformationMatrix display_matrix);
        Math::ivec3 GetHotSpot(int index);
        Math::ivec3 GetFrameSize();

        void PlayAnimation(int animation);
        bool AnimationEnded();
    private:
        Math::ivec3 GetFrameTexel(int index) const;

        Texture* texture;
        std::vector<Math::ivec3> hotspots;

        int current_animation;
        Math::ivec3 frame_size;
        std::vector<Math::ivec3> frame_texels;
        std::vector<Animation*> animations;
    };
}
