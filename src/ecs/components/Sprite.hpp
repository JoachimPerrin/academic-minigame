/**
 * @file Sprite.hpp
 * @author Joachim Perrin (joachimperrin1@gmail.com)
 * @brief This file contains the definition of the Sprite class, which is a component that allows entities to have a sprite.
 * @version 0.1
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef __SPRITE__
#define __SPRITE__

#include "ECS.hpp"
#include "Transform.hpp"
#include "Animation.hpp"
#include <map>
#include <SDL2/SDL.h>

namespace ecs
{
    /**
     * @brief The Sprite class is a component that allows entities to have a sprite.
     *
     */
    class Sprite : public Component
    {
    public:
        Sprite(std::string id, bool isAnimated = false);

        void Init() override;
        void Update() override;
        void Render() override;

        void SetTexture(std::string id);
        void Play(const std::string animName);

        int animIndex = 0;
        std::map<const std::string, Animation> animations;
        SDL_RendererFlip spriteflip = SDL_FLIP_NONE;

    private:
        Transform *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect;
        SDL_Rect destRect;

        bool animated;
        int frame = 0;
        int speed = 100; // delay between frames in ms
    };
}
#endif