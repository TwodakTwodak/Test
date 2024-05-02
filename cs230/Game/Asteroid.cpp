#include "Mode1.h"
#include "../Engine/Engine.h"
#include "Asteroid.h"

Asteroid::Asteroid(Math::vec2 start_position) :
    GameObject(start_position)
{
    current_state = &state_landing;
    sprite.Load("Assets/Asteroid.spt");
    current_state->Enter(this);
}

//Bounce
void Asteroid::State_Bouncing::Enter(GameObject* object) {
    Asteroid* asteroid = static_cast<Asteroid*>(object);
    asteroid->sprite.PlayAnimation(static_cast<int>(Animations::Bouncing));
    asteroid->SetVelocity({ 0, Asteroid::bounce_velocity });
}
void Asteroid::State_Bouncing::Update(GameObject* object, double dt) {
    Asteroid* asteroid = static_cast<Asteroid*>(object);
    asteroid->UpdateVelocity({ 0, -(Mode1::gravity * dt) });
}
void Asteroid::State_Bouncing::CheckExit(GameObject* object) {
    Asteroid* asteroid = static_cast<Asteroid*>(object);
    if (asteroid->GetPosition().y < Mode1::floor) {
        asteroid->SetPosition({ asteroid->GetPosition().x, Mode1::floor });
        asteroid->SetVelocity({ 0, 0 });
        asteroid->change_state(&asteroid->state_landing);
    }
}

//Land
void Asteroid::State_Landing::Enter(GameObject* object) {
    Asteroid* asteroid = static_cast<Asteroid*>(object);
    asteroid->sprite.PlayAnimation(static_cast<int>(Animations::Landing));
    asteroid->SetVelocity({0, 0});
    asteroid->SetPosition({ asteroid->GetPosition().x, Mode1::floor });
}
void Asteroid::State_Landing::Update(GameObject* object, double dt) { }
void Asteroid::State_Landing::CheckExit(GameObject* object) {
    Asteroid* asteroid = static_cast<Asteroid*>(object);
    if (asteroid->sprite.AnimationEnded()) {
        asteroid->change_state(& asteroid->state_bouncing);
    }
}
