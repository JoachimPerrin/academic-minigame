/**
 * @file GoManager.hpp
 * @author Joachim Perrin (joachimperrin1@gmail.com)
 * @brief This file contains the definition of the GoManager class, which is a class that manages the creation of game objects.
 * @version 0.1
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef GoMANAGER__HPP
#define GoMANAGER__HPP

#include "Vector2.hpp"
#include "Enemy.hpp"
#include "Projectile.hpp"
#include <array>

/**
 * @brief The GoManager class is a class that manages the creation of game objects.
 *
 */
class GoManager
{
public:
    GoManager(ecs::EntitiesManager *man) : manager(man) {}

    ecs::Entity *CreatePlayer(int numplayer);
    void CreateEnemy(Vector2 position, ecs::EnemyType type);
    void CreateProjectile(Vector2 position, Vector2 velocity, int range, int speed, ecs::ProjectileType type);
    void CreateButton(SDL_Rect bbox, std::string text = "");

private:
    ecs::EntitiesManager *manager;
};

#endif