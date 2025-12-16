#include "AudioManager.hpp"
#include "Game.hpp"
#include <iostream>
#include <SDL2/SDL_mixer.h>

Mix_Music *AudioManager::LoadAudio(const std::string musicPath)
    {
        Mix_Music *newMusic = Mix_LoadMUS(musicPath.c_str());
        std::cout << "Chargement musique: " << Mix_LoadMUS(musicPath.c_str()) << std::endl;
        if (!newMusic)
        {
            std::cerr << "Erreur chargement musique: " << Mix_GetError() << std::endl;
        }
        return newMusic;
    }
Mix_Music* AudioManager::PlayAudio(Mix_Music* music, bool loop) {
    if (music) {
        Mix_PlayMusic(music, loop ? -1 : 0);
    } else {
        std::cerr << "Erreur: musique non chargée." << std::endl;
    }
    return music;
}

void AudioManager::StopAudio() {
    Mix_HaltMusic();
}

