#include "MenuState.hpp"
#include "Game.hpp"
#include <iostream>

auto &buttons = Game::manager.GetGroup(Game::buttons);

MenuState::MenuState()
{
    std::cout << "Creating Menu..." << std::endl;
}

MenuState::~MenuState()
{
    std::cout << "Destroying Menu..." << std::endl;
}

void MenuState::Enter(Game &game)
{
    if (game.IsRunning())
        std::cout << "Entering Menu" << std::endl;
    Game::gobjs->CreateButton(SDL_Rect({(Window_W) / 2 - 300, (Window_H) / 2 - 150, 200, 100}), "Play");
}

void MenuState::Exit(Game &game)
{
    for (auto &b : buttons)
    {
        b->Render();
    }
    if (game.IsRunning())
        std::cout << "Exiting Menu" << std::endl;
}

void MenuState::HandleEvent(Game &game)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT ||
            (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
        {
            game.running = false;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
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
                break;

            case SDLK_r:
                game.ChangeState(game.playingState);
                break;

            default:
                break;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.clicks >= 2)
                game.ChangeState(game.playingState);
        }
    }
}

void MenuState::Update(Game &game)
{
    for (auto &b : buttons)
    {
        b->Update();
    }
    if (game.IsRunning())
        return;
}

void MenuState::Render(Game &game)
{
    for (auto &b : buttons)
    {
        b->Render();
    }
    if (game.IsRunning())
        return;
}