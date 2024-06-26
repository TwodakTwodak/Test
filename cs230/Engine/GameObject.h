/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObject.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include "Sprite.h"

namespace Math { class TransformationMatrix; }

namespace CS230 {
    class GameObject {
    public:
        GameObject();
        GameObject(Math::vec3 position);
        GameObject(Math::vec3 position, double rotation, Math::vec3 scale);
        virtual ~GameObject() {}

        virtual void Update(double dt);
        virtual void Draw(Math::TransformationMatrix camera_matrix);

        const Math::TransformationMatrix& GetMatrix();
        const Math::vec3& GetPosition() const;
        const Math::vec3& GetVelocity() const;
        const Math::vec3& GetScale() const;
        double GetRotation() const;

    protected:
        class State {
        public:
            virtual void Enter(GameObject* object) = 0;
            virtual void Update(GameObject* object, double dt) = 0;
            virtual void CheckExit(GameObject* object) = 0;
            virtual std::string GetName() = 0;
        };
        State* current_state = nullptr;
        void change_state(State* new_state);

        void SetPosition(Math::vec2 new_position);
        void UpdatePosition(Math::vec2 delta);
        void SetVelocity(Math::vec2 new_velocity);
        void UpdateVelocity(Math::vec2 delta);
        void SetScale(Math::vec2 new_scale);
        void UpdateScale(Math::vec2 delta);
        void SetRotation(double new_rotation);
        void UpdateRotation(double delta);

        Sprite sprite;

    private:
        //none 
        class State_None : public State {
        public:
            void Enter(GameObject*) override {}
            void Update(GameObject*, double) override {}
            void CheckExit(GameObject*) override {}
            std::string GetName() { return ""; }
        };
        State_None state_none;

        Math::TransformationMatrix object_matrix;

        bool matrix_outdated = false;

        double rotation;
        Math::vec3 scale;
        Math::vec3 position;
        Math::vec3 velocity;
    };
}
