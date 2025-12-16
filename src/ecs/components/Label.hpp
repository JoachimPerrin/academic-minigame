#ifndef LABELS_HPP
#define LABELS_HPP

#include "ECS.hpp"
#include "Transform.hpp"
#include <SDL2/SDL.h>
#include <string>

namespace ecs
{
    /**
     * @brief This component describe a label, it depends on a Transform component
     * @note This class depends on a Transform component, so it is recommended to initialize one first.
     *
     */
    class Label : public Component
    {
    public:
        Label(SDL_Rect dst, std::string text, bool mobile = false, SDL_Color color = {255, 255, 255, 255}, std::string font = "Dundalk");

        void SetText(std::string text);
        void SetFont(std::string font);
        void SetColor(SDL_Color color);

        void Init() override;
        void Render() override;
        void Update() override;

    private: // FIXME: ces variables doivent pour certaines redevenir public
        void SetLabelText();

        Transform *transform;
        SDL_Texture *labelTexture;

        SDL_Rect dstRect;
        SDL_Rect srcRect;

        std::string text;
        bool mobile;
        SDL_Color color;
        std::string font;
    };
}

#endif