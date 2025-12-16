#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Utils.hpp"
#include <memory>
#include <vector>
#include <SDL2/SDL.h>

class Game;

class GameState
{
public:
    virtual ~GameState() = default;

    virtual void Enter(Game &game) = 0;
    virtual void Exit(Game &game) = 0;
    virtual void HandleEvent(Game &game) = 0;
    virtual void Update(Game &game) = 0;
    virtual void Render(Game &game) = 0;

    template <typename T>
    void Execute(T Input);
};

#endif