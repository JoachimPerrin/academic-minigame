/**
 * @file AssetsManager.hpp
 * @author Joachim Perrin (joachimperrin1@gmail.com)
 * @brief This file contains the definition of the AssetManager class, which is a class that manages the assets of the game.
 * @version 0.1
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "ECS.hpp"
#include "AudioManager.hpp"

/**
 * @brief The AssetManager class is a class that manages the assets of the game.
 *
 */
class AssetManager
{
public:
    AssetManager();
    ~AssetManager();

    void ClearTextures();
    void AddTexture(std::string id, const std::string path);
    SDL_Texture *GetTexture(std::string id);

    void AddFont(std::string id, const std::string path, int fontSize);
    TTF_Font *GetFont(std::string id);

    void AddAudio(std::string id, const std::string path);
    Mix_Music *GetAudio(std::string id);

private:
    std::map<std::string, SDL_Texture *> textures;
    std::map<std::string, TTF_Font *> fonts;
    std::map<std::string, Mix_Music *> audios;
};

#endif