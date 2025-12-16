#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>

class AudioManager {
public:
    static Mix_Music *LoadAudio(const std::string musicPath);
    static Mix_Music *PlayAudio(Mix_Music* music, bool loop);
    static void StopAudio();
};

#endif 
