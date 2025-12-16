#include "CollisionManager.hpp"
#include "ComponentManager.hpp"
#include "Label.hpp"
#include "Game.hpp"

void CollisionManager::GlideCollision(ecs::Entity *entity, Vector2 vec)
{
    if (entity->HasComponent<ecs::Transform>())
    {
        Vector2 normal = vec.Normal();
        Vector2 vel = entity->GetComponent<ecs::Transform>().GetVel();
        if (vel.Project(vel, vec).x * vec.x > 0 || vel.Project(vel, vec).y * vec.y > 0)
        {
            if (entity->HasComponent<ecs::Label>())
                vec = Vector2();
            ecs::ComponentManager::EntitySetVelocity(*entity, vel.Project(vel, normal) - vec);
        }
    }
}

void CollisionManager::ReboundCollision(ecs::Entity *entity, Vector2 vec)
{
    if (entity->HasComponent<ecs::Transform>())
    {
        // Reverse the velocity based on the normal
        if ((vec * Vector2(0.01, 0.01)).magnitude() > 0.3)
        {
            // TODO: ComponentManager
            entity->GetComponent<ecs::Transform>().SetVel(vec * Vector2(0.005, 0.005));
        }
    }
}

void CollisionManager::ProjectileCollision(ecs::Entity *entity)
{
    if (entity->HasComponent<ecs::Stat>())
    {
        entity->Destroy();
    }
}

void CollisionManager::Update(ecs::EntitiesManager &EMan)
{
    std::vector<ecs::Entity *> colidable = EMan.GetGroup(Game::collidable);
    std::vector<ecs::Entity *> players = EMan.GetGroup(Game::players);
    std::vector<ecs::Entity *> enemies = EMan.GetGroup(Game::enemies);
    std::vector<ecs::Entity *> projectiles = EMan.GetGroup(Game::projectiles);
    Vector2 nullvect = Vector2(0, 0);
    Vector2 vec;

    for (auto &player : players)
    {
        for (auto &col : colidable)
        {
            if (player->HasComponent<ecs::CircularCollider>() && col->HasComponent<ecs::AABBCollider>())
            {
                vec = player->GetComponent<ecs::CircularCollider>().IsColliding(col->GetComponent<ecs::AABBCollider>());
                if (vec != nullvect)
                {
                    // std::cout << "Collision" << std::endl;
                    GlideCollision(player, vec);
                }
            }
        }
        for (auto &enemy : enemies)
        {
            if (player->HasComponent<ecs::CircularCollider>() && enemy->HasComponent<ecs::CircularCollider>())
            {
                vec = player->GetComponent<ecs::CircularCollider>().IsColliding(enemy->GetComponent<ecs::CircularCollider>());
                if (vec != nullvect)
                {
                    ReboundCollision(player, vec);
                }
            }
        }
    }
    for (auto &enemy : enemies)
    {
        for (auto &player : players)
        {
            if (enemy->HasComponent<ecs::CircularCollider>() && player->HasComponent<ecs::CircularCollider>())
            {
                vec = enemy->GetComponent<ecs::CircularCollider>().IsColliding(player->GetComponent<ecs::CircularCollider>());
                if (vec != nullvect)
                {
                    ReboundCollision(enemy, vec);
                    if (player->HasComponent<ecs::Stat>())
                    {
                        player->GetComponent<ecs::Stat>().Hurt(1);
                    }
                }
            }
        }
        for (auto &col : colidable)
        {
            if (enemy->HasComponent<ecs::CircularCollider>() && col->HasComponent<ecs::AABBCollider>())
            {
                vec = enemy->GetComponent<ecs::CircularCollider>().IsColliding(col->GetComponent<ecs::AABBCollider>());
                if (vec != nullvect)
                {
                    GlideCollision(enemy, vec);
                }
            }
        }
    }
    for (auto &projectile : projectiles)
    {
        for (auto &enemy : enemies)
        {
            if (projectile->HasComponent<ecs::CircularCollider>() && enemy->HasComponent<ecs::CircularCollider>())
            {
                vec = projectile->GetComponent<ecs::CircularCollider>().IsColliding(enemy->GetComponent<ecs::CircularCollider>());
                if (vec != nullvect)
                {
                    projectile->Destroy();
                    if (enemy->HasComponent<ecs::Stat>())
                    {
                        enemy->GetComponent<ecs::Stat>().Hurt(500);
                    }
                }
            }
        }
        for (auto &col : colidable)
        {
            if (projectile->HasComponent<ecs::CircularCollider>() && col->HasComponent<ecs::AABBCollider>())
            {
                vec = projectile->GetComponent<ecs::CircularCollider>().IsColliding(col->GetComponent<ecs::AABBCollider>());
                if (vec != nullvect)
                {
                    projectile->Destroy();
                }
            }
        }
    }
}
