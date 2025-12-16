#include "TextureManager.hpp"
#include "Game.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>

SDL_Texture *TextureManager::LoadTexture(const std::string imagePath)
{
    SDL_Surface *tempSurface = nullptr;
    SDL_Texture *newTexture = nullptr;
    tempSurface = IMG_Load(imagePath.c_str());
    if (tempSurface == nullptr)
    {
        std::cerr << "Echec de chargement de l'image " << imagePath << "! SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    newTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    if (newTexture == nullptr)
    {
        std::cerr << "Echec de la création de la texture à partir de la surface ! SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    return newTexture;
}

void TextureManager::Render(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip renderflip)
{
    if (tex == nullptr)
    {
        std::cerr << "Texture is nullptr, cannot render!" << std::endl;
        return;
    }
    // Si elle est visible, on l'affiche
    if (SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, 0.0, nullptr, renderflip))
    {
        std::cerr << "Echec d'affichage de la texture ! " << SDL_GetError() << std::endl;
    }
}
