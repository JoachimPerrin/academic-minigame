#include "Game.hpp"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Utils.hpp"

SDL_Renderer *Game::renderer = nullptr;
AssetManager *Game::assets = new AssetManager();
GoManager *Game::gobjs = new GoManager(&Game::manager);
ecs::EntitiesManager Game::manager;
SDL_Event Game::event;

Game::Game()
    : window(nullptr), running(true)
{
    InitSDL();
    InitWindow("I am having SOOO MUCH fun right now !", Window_W, Window_H, SDL_FALSE);
    InitRenderer();
    Initialize();
}

void Game::InitSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
    {
        ExitWithError("Echec d'initialisation de la bibliothèque SDL");
        running = SDL_FALSE;
    }
    std::cout << "SDL initialisée..." << std::endl;

    if (TTF_Init() == -1)
    {
        ExitWithError("Echec d'initialisation de la bibliothèque TTF");
    }
    std::cout << "TTF initialisé..." << std::endl;

    if (Mix_OpenAudio(AUDIO_FREQ, MIX_DEFAULT_FORMAT, NB_CHANNELS, CHUNK_SIZE) < 0)
    {
        ExitWithError("Echec d'initialisation de la bibliothèque SDL_mixer");
    }
    std::cout << "SDL_mixer initialisé..." << std::endl;
}

void Game::InitWindow(const std::string &title, int width, int height, SDL_bool fullscreen)
{
    int flags = SDL_WINDOW_SHOWN;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if (window == nullptr)
    {
        ExitWithError("Echec de création de la fenêtre");
    }
    std::cout << "Fenêtre créée..." << std::endl;
}

void Game::InitRenderer()
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        ExitWithError("Echec de création du rendu", window);
    }
    std::cout << "Rendu créé..." << std::endl;
}

void Game::Initialize()
{
    assets->AddTexture("Robot", "assets/images/ARobot.png");
    assets->AddTexture("ColMark", "assets/images/ColliderMark.png");
    assets->AddTexture("LobbyTileSet", "assets/images/TSLobby.png");
    assets->AddTexture("enemy", "assets/images/AEnemies.png");
    assets->AddTexture("projectile", "assets/images/AProjectiles.png");
    assets->AddTexture("button", "assets/images/Button.png");

    assets->AddFont("Dundalk", "assets/fonts/Dundalk.otf", 16);

    assets->AddAudio("BackgroundMusic", "assets/audios/Theme1JC.mp3");

    menuState = std::make_unique<MenuState>();
    playingState = std::make_unique<PlayingState>();
    pausedState = std::make_unique<PausedState>();

    currentState = menuState;
    currentState->Enter(*this);
}

bool Game::IsRunning() const
{
    return running;
}

void Game::HandleEvents()
{
    if (currentState)
    {
        currentState->HandleEvent(*this);
    }
}

void Game::ChangeState(std::shared_ptr<GameState> newState)
{
    if (!newState)
    {
        std::cerr << "Error: Attempted to switch to a null state!" << std::endl;
        return;
    }

    if (currentState)
        currentState->Exit(*this);

    currentState = newState;
    currentState->Enter(*this);
}

void Game::Update()
{
    if (currentState)
    {
        currentState->Update(*this);
    }
}

void Game::Render()
{
    if (currentState)
    {
        if (SDL_RenderClear(renderer) != 0)
        {
            std::cerr << "Echec de nettoyage du rendu: " << SDL_GetError() << std::endl;
            return;
        }

        currentState->Render(*this);

        SDL_RenderPresent(renderer);
    }
}

void Game::Cleanup()
{
    // Cleanup dynamically allocated resources
    // if (renderer != nullptr)
    // {
    //     SDL_DestroyRenderer(renderer);
    //     std::cout << "Rendu détruit" << std::endl;
    // }
    assets->ClearTextures();
    if (window)
    {
        SDL_DestroyWindow(window);
        std::cout << "Fenêtre détruite" << std::endl;
    }
    //Mix_FreeMusic(music);
    Mix_CloseAudio();
    TTF_Quit();
    std::cout << "TTF quitté" << std::endl;
    IMG_Quit();
    std::cout << "IMG quitté" << std::endl;
    SDL_Quit();
    std::cout << "SDL quittée" << std::endl;
}
