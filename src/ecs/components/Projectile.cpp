#include "Projectile.hpp"
#include "Game.hpp"
#include <cmath>

namespace ecs
{
    Projectile::Projectile(int rng, Vector2 v, ProjectileType t)
        : velocity(v), type(t), range(rng)
    {
        speed = std::sqrt(std::pow(v.x, 2) + std::pow(v.y, 2));
    }

    void Projectile::Init()
    {
        transform = &entity->GetComponent<Transform>();
        transform->velocity = velocity;
        distance = 0;
    }

    void Projectile::Update()
    {
        distance += speed;
        if (distance > range)
        {
            std::cout << "out of range" << std::endl;
            entity->Destroy();
        }
        else if (transform->GetPos().x > PlayingState::camera.x + PlayingState::camera.w ||
                 transform->GetPos().x < PlayingState::camera.x ||
                 transform->GetPos().y > PlayingState::camera.y + PlayingState::camera.h ||
                 transform->GetPos().y < PlayingState::camera.y)
        {
            std::cout << "out of bounds" << std::endl;
            entity->Destroy();
        }
    }
    ProjectileType Projectile::GetType() { return type; }
}