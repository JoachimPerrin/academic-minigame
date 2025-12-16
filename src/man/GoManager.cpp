#include "GoManager.hpp"
#include "Game.hpp"
#include "Transform.hpp"
#include "Collider.hpp"
#include "Sprite.hpp"
#include "Projectile.hpp"
#include "Stat.hpp"
#include "Label.hpp"
#include "FSM.hpp"
#include "ComponentManager.hpp"
#include "Utils.hpp"
#include <SDL2/SDL.h>

ecs::Entity *GoManager::CreatePlayer(int numplayer)
{
    auto &player(Game::manager.AddEntity());
    player.AddComponent<ecs::Transform>(Vector2(500.0f, 700.0f), Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2(3.0f, 3.0f));
    player.AddComponent<ecs::Sprite>("Robot", true);
    // player.AddComponent<ecs::KeyboardController>();
    player.AddComponent<ecs::Stat>();
    player.AddComponent<ecs::CircularCollider>("Robot");

    // FSM
    //  TODO: Matrice des transitions pour le joueur
    std::array<std::array<PlayerState, nbPlayerInputs>, nbPlayerStates> transitions = {{
        // I_MOVE                           I_INVENTORY                        I_ATTACK                          I_NONE
        {PlayerState::S_RUNNING_JOUEUR, PlayerState::S_INVENTORY_JOUEUR, PlayerState::S_IDLE_JOUEUR, PlayerState::S_IDLE_JOUEUR},       // Etat IDLE
        {PlayerState::S_RUNNING_JOUEUR, PlayerState::S_INVENTORY_JOUEUR, PlayerState::S_RUNNING_JOUEUR, PlayerState::S_IDLE_JOUEUR},    // Etat RUNNING
        {PlayerState::S_INVENTORY_JOUEUR, PlayerState::S_IDLE_JOUEUR, PlayerState::S_INVENTORY_JOUEUR, PlayerState::S_INVENTORY_JOUEUR} // Etat INVENTAIRE
    }};

    // Table des actions pour le joueur
    // TODO: VOIR SI JOEUR 1 OU 2 PR SAVOIR QUEL KEYS DONNEE
    // Joueur 1
    std::array<std::array<std::function<void()>, nbPlayerInputs>, nbPlayerStates> actions;
    if (numplayer == 1)
    {
        player.AddComponent<ecs::Label>(SDL_Rect({0, 0, 80, 15}), "Jason-1012", true);
        actions = {{
            {[&player]()
             { ecs::ComponentManager::JoueurMouvement(keysP1, player); }, [&player]()
             { ecs::ComponentManager::InventaireOpen(player); }, [&player]()
             { ecs::ComponentManager::Tir(keysP1, player); }, [&player]()
             { ecs::ComponentManager::JoueurStopMouvement(player); }}, // IDLE
            {[&player]()
             { ecs::ComponentManager::JoueurMouvement(keysP1, player); }, [&player]()
             { ecs::ComponentManager::InventaireOpen(player); }, [&player]()
             { ecs::ComponentManager::Tir(keysP1, player); }, [&player]()
             { ecs::ComponentManager::JoueurStopMouvement(player); }}, // RUNNING, /* additional arguments */
            {[]() {}, [&player]()
             { ecs::ComponentManager::InventaireClose(player); }, []() {}, []() {}} // INVENTAIRE

        }};
    }
    // Joueur 2
    else
    {
        player.AddComponent<ecs::Label>(SDL_Rect({0, 0, 80, 15}), "Brandon-7528", true);
        actions = {{
            {[&player]()
             { ecs::ComponentManager::JoueurMouvement(keysP2, player); }, [&player]()
             { ecs::ComponentManager::InventaireOpen(player); }, [&player]()
             { ecs::ComponentManager::Tir(keysP2, player); }, [&player]()
             { ecs::ComponentManager::JoueurStopMouvement(player); }}, // IDLE
            {[&player]()
             { ecs::ComponentManager::JoueurMouvement(keysP2, player); }, [&player]()
             { ecs::ComponentManager::InventaireOpen(player); }, [&player]()
             { ecs::ComponentManager::Tir(keysP2, player); }, [&player]()
             { ecs::ComponentManager::JoueurStopMouvement(player); }}, // RUNNING, /* additional arguments */
            {[]() {}, [&player]()
             { ecs::ComponentManager::InventaireClose(player); }, []() {}, []() {}} // INVENTAIRE

        }};
    }

    player.AddComponent<ecs::FSM<PlayerState, PlayerInput, nbPlayerStates, nbPlayerInputs>>(
        PlayerState::S_IDLE_JOUEUR, // État initial (ici, exemple pour un joueur)
        transitions,                // Matrice des transitions
        actions                     // Table des actions
    );

    player.AddGroup(Game::players);
    player.AddGroup(Game::controllables);
    return &player;
}

void GoManager::CreateProjectile(Vector2 position, Vector2 velocity, int range, int speed, ecs::ProjectileType type)
{
    auto &projectile(manager->AddEntity());
    projectile.AddComponent<ecs::Transform>(Vector2(position.x, position.y), Vector2(speed, speed), Vector2(32, 32), Vector2(1, 1));
    projectile.AddComponent<ecs::Sprite>("projectile", true);
    if (type == ecs::hostileProjectile)
    {
        projectile.GetComponent<ecs::Sprite>().Play("HostileBullet");
    }
    else if (type == ecs::allyProjectile)
    {
        projectile.GetComponent<ecs::Sprite>().Play("AllyBullet");
    }
    else if (type == ecs::chargedProjectile)
    {
        projectile.GetComponent<ecs::Sprite>().Play("ChargedBullet");
    }
    projectile.AddComponent<ecs::CircularCollider>("projectile");
    projectile.AddComponent<ecs::Projectile>(range, velocity, type);
    projectile.AddGroup(Game::projectiles);
    projectile.AddGroup(Game::controllables);
}

void GoManager::CreateEnemy(Vector2 position, ecs::EnemyType type)
{
    auto &enemy(manager->AddEntity());
    float speed_x = rand() % 16 / 10.0f;
    float speed_y = rand() % 16 / 10.0f;
    std::cout << "speed_x : " << speed_x << " speed_y : " << speed_y << std::endl;
    enemy.AddComponent<ecs::Transform>(Vector2(position.x, position.y), Vector2(speed_x, speed_y), Vector2(32.0f, 32.0f), Vector2(3.0f, 3.0f));
    enemy.AddComponent<ecs::Sprite>("enemy", true);
    enemy.AddComponent<ecs::Stat>();
    if (type == ecs::bat)
    {
        enemy.GetComponent<ecs::Sprite>().Play("Bat");
        enemy.AddComponent<ecs::CircularCollider>("Bat");
    }
    else if (type == ecs::spider)
    {
        enemy.GetComponent<ecs::Sprite>().Play("Spider");
        enemy.AddComponent<ecs::CircularCollider>("Spider");
    }
    else if (type == ecs::snake)
    {
        enemy.GetComponent<ecs::Sprite>().Play("Snake");
        enemy.AddComponent<ecs::CircularCollider>("Snake");
    }
    enemy.AddGroup(Game::enemies);
    enemy.AddGroup(Game::controllables);
}

void GoManager::CreateButton(SDL_Rect bbox, std::string text)
{
    auto &button(manager->AddEntity());
    button.AddComponent<ecs::Transform>(Vector2(bbox.x, bbox.y), Vector2(0, 0), Vector2(bbox.w, bbox.h), Vector2(3.0, 3.0));
    button.AddComponent<ecs::Sprite>("button");
    // button.AddComponent<ecs::Gui>();
    SDL_Rect centeredBbox = {bbox.x + (bbox.w), bbox.y + (bbox.h), bbox.w, bbox.h};
    button.AddComponent<ecs::Label>(centeredBbox, text);
    button.AddGroup(Game::buttons);
}
