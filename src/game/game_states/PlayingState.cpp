#include "PlayingState.hpp"
#include "Transform.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "FSM.hpp"
#include "Sprite.hpp"
#include <iostream>

#define NB_SPIDER 150
#define NB_BAT 150

SDL_Rect PlayingState::camera = {0, 0, Window_W, Window_H};
MapManager *PlayingState::mapManager = new MapManager();
CollisionManager *collisions = new CollisionManager();

auto &players(Game::manager.GetGroup(Game::players));
auto &enemy(Game::manager.GetGroup(Game::enemies));
auto &tiles(Game::manager.GetGroup(Game::maps));
auto &collidables(Game::manager.GetGroup(Game::collidable));
auto &projectiles(Game::manager.GetGroup(Game::projectiles));

ecs::Entity *Player;

PlayingState::PlayingState()
{
    std::cout << "ajout de la map\n"
              << std::endl;
    mapManager->AddMap("LobbyMap", "assets/maps/TMLobby.txt", 25, 20);
    std::cout << "\nmap ajouté" << std::endl;
    mapManager->LoadMap("LobbyMap", "LobbyTileSet");
    // TODO: bien faire les initialisations nécessaire ici
}

PlayingState::~PlayingState()
{
    Game::manager.ClearEntities(-1);
    delete mapManager;
    delete collisions;
    std::cout << "score : " << score << std::endl
              << "Destroying Playing state" << std::endl;
}

void PlayingState::Enter(Game &game)
{
    // TODO: quelques initialisation devraient peut-être apparaître ici
    if (game.IsRunning())
    {
        std::cout << "Entering Playing State" << std::endl;
        Player = Game::gobjs->CreatePlayer(1);
        Game::gobjs->CreatePlayer(2);
        for (int i = 0; i < NB_SPIDER; i++)
            Game::gobjs->CreateEnemy(Vector2(2400.0f, 630.0f), ecs::spider);
        for (int i = 0; i < NB_BAT; i++)
            Game::gobjs->CreateEnemy(Vector2(2400.0f, 630.0f), ecs::bat);

        PlayBackgroundMusic();
    }
}

void PlayingState::Exit(Game &game)
{
    // TODO: sûrement des trucs à faire ici aussi
    Game::manager.ClearEntities(Game::players);
    Game::manager.ClearEntities(Game::enemies);
    Game::manager.ClearEntities(Game::projectiles);
    std::cout << "Exiting Playing State" << std::endl;
    if (game.IsRunning())
        return;
}

void PlayingState::HandleEvent(Game &game)
{
    // TODO: implémenter les gestions d'evenements ici
    SDL_Event event = game.event;

    // Action qui demandent plusieurs touche simultanement
    Execute(actions[currentState][I_MOVE_P1]);
    // Execute(actions[currentState][I_MOVE_P2]);

    Execute(actions[currentState][I_ATTACK_P1]);
    Execute(actions[currentState][I_ATTACK_P2]);

    while (SDL_PollEvent(&event))
    {
        // TODO: Ce qui suit est pr la machine a etat generale a changer
        if (event.type == SDL_QUIT ||
            (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
        {
            game.running = false;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {

            // Ici on gère les entrées qui change l'etat globale du jeu
            case SDLK_ESCAPE:

                // TODO: ICI On doit faire intervenir machine a etat global en donnant l'entree p

                game.running = false;
                break;

            case SDLK_p:
                if (dynamic_cast<PlayingState *>(game.currentState.get()))
                {
                    game.ChangeState(game.pausedState);
                }
                else if (dynamic_cast<PausedState *>(game.currentState.get()))
                {
                    game.ChangeState(game.playingState);
                }
                // TODO: ICI On doit faire intervenir machine a etat global en donnant l'entree p

                break;

            case SDLK_r:
                game.ChangeState(game.playingState);
                break;

            // A PARTIR D'ICI On manage gère les entrées qui n'ont aucun rapport avec la changement d'etat globale
            //  TODO: voir inventaire pr differents joueur 2 + Ajouter fsm de playingstate
            //  Inventaire
            case SDLK_e:
                Execute(actions[currentState][I_INV_P1]);
                break;

            default:
                break;
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            Execute(A_NONE);
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            // TODO: Appeler la fonction de la machine a etat de playingstate avec la touche appuyer ici (en argument event.button.clicks)
            if (event.button.clicks >= 2)
                game.ChangeState(game.pausedState);
        }
    }
}

bool PlayingState::Execute(const PlayingActions action)
{

    // Conditions

    for (auto &p : players)
    {
        if (!p->HasComponent<ecs::FSM<PlayerState, PlayerInput, nbPlayerStates, nbPlayerInputs>>())
            return false;
        auto &playerFSM = p->GetComponent<ecs::FSM<PlayerState, PlayerInput, nbPlayerStates, nbPlayerInputs>>();
        switch (action)
        {
        case A_NONE:
            break;

        case A_MOVE_P1: // TODO: A modifier pour joueur 1 ou 2

            playerFSM.handleInput(I_MOVE);

            break;
        case A_MOVE_P2:
            // TODO:

            break;
        case A_ATTACK_P1:
            playerFSM.handleInput(I_ATTACK);
            break;
        case A_ATTACK_P2:

            break;
        case A_JUMP:
            break;
        case A_INVENTORY_P1: // TODO: ICI MACHINE A ETAT DU JOUEUR (on le fait passer en mode inventaire)

            playerFSM.handleInput(I_INVENTORY);

            break;
        case A_INVENTORY_P2:
            break;
        case A_RUN:
            break;
        case A_USE_ITEM:
            break;
        }
    }

    // TODO: Rajouter
    return true;
}

void PlayingState::Update(Game &game)
{
    // TODO: ajouter la logique d'update ici
    if (game.IsRunning())
    {
        collisions->Update(Game::manager);
        Game::manager.Refresh();
        Game::manager.Update();

        if (!Player->IsActive())
        {
            game.ChangeState(game.playingState);
        }

        // Caméra centrée sur le joueur
        camera.x = Player->GetComponent<ecs::Transform>().GetPos().x - (Window_W - Player->GetComponent<ecs::Transform>().GetSize().x) / 2; // camera.w/2
        camera.y = Player->GetComponent<ecs::Transform>().GetPos().y - (Window_H - Player->GetComponent<ecs::Transform>().GetSize().y) / 2;
        // Caméra limitée par la bordure de la map
        if (camera.x < 0)
            camera.x = 0;
        if (camera.y < 0)
            camera.y = 0;
        if (camera.x > mapManager->GetCurrentMap()->GetBounds().x - camera.w)
            camera.x = mapManager->GetCurrentMap()->GetBounds().x - camera.w;
        if (camera.y > mapManager->GetCurrentMap()->GetBounds().y - camera.h)
            camera.y = mapManager->GetCurrentMap()->GetBounds().y - camera.h;
    }
}

void PlayingState::Render(Game &game)
{
    // TODO: ajouter les affichages ici (l'ordre est important)
    if (game.IsRunning())
    {
        for (auto &t : tiles)
        {
            t->Render();
        }
        for (auto &p : players)
        {
            p->Render();
        }
        for (auto &e : enemy)
        {
            e->Render();
        }
        for (auto &p : projectiles)
        {
            p->Render();
        }

        // for (auto &c : collidables)
        // {
        //     c->Render();
        // }
    }
}

void PlayingState::PlayBackgroundMusic()
{
    BackgroundMusic = AudioManager::LoadAudio("assets/audios/Theme1JC.mp3");
    AudioManager::PlayAudio(BackgroundMusic, true);
}
