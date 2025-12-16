#include "Utils.hpp"
#include <SDL2/SDL_ttf.h>
#include <cmath>

SDL_Scancode keysP1[7] = {
    SDL_SCANCODE_UP,
    SDL_SCANCODE_DOWN,
    SDL_SCANCODE_LEFT,
    SDL_SCANCODE_RIGHT,
    SDL_SCANCODE_SPACE,
    SDL_SCANCODE_L,
    SDL_SCANCODE_K
};
SDL_Scancode keysP2[7] = {
    SDL_SCANCODE_W,
    SDL_SCANCODE_S,
    SDL_SCANCODE_A,
    SDL_SCANCODE_D,
    SDL_SCANCODE_SPACE,
    SDL_SCANCODE_C,
    SDL_SCANCODE_V
};

void ExitWithError(const std::string str, SDL_Window *w, SDL_Renderer *r)
{
    if (r != nullptr)
        SDL_DestroyRenderer(r);
    if (w != nullptr)
        SDL_DestroyWindow(w);
    SDL_Quit();
    TTF_Quit();
    throw std::runtime_error(str + " SDL_Error: " + std::string(SDL_GetError()));
    exit(EXIT_FAILURE);
}

std::ostream &operator<<(std::ostream &stream, const SDL_Rect &rect)
{
    stream << "{" << rect.x << "," << rect.y << "," << rect.w << "," << rect.h << "}";
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const SDL_FRect &rect)
{
    stream << "{" << rect.x << "," << rect.y << "," << rect.w << "," << rect.h << "}";
    return stream;
}

SDL_Rect FRectToRect(const SDL_FRect &fRect)
{
    return SDL_Rect{
        static_cast<int>(std::round(fRect.x)),
        static_cast<int>(std::round(fRect.y)),
        static_cast<int>(std::round(fRect.w)),
        static_cast<int>(std::round(fRect.h))};
}