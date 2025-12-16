#include "Label.hpp"
#include "Vector2.hpp"
#include "AssetsManager.hpp"
#include "Game.hpp"
#include "PlayingState.hpp"

#include <SDL2/SDL_ttf.h>

namespace ecs
{
    Label::Label(SDL_Rect dst, std::string text, bool mob, SDL_Color color, std::string font)
        : dstRect(dst), text(text), mobile(mob), color(color), font(font)
    {
        SetLabelText();
    }

    void Label::SetText(std::string tex)
    {
        text = tex;
        SetLabelText();
    }

    void Label::SetFont(std::string fon)
    {
        font = fon;
        SetLabelText();
    }

    void Label::SetColor(SDL_Color colo)
    {
        color = colo;
        SetLabelText();
    }

    void Label::Init()
    {
        if (!entity->HasComponent<Transform>())
        {
            entity->AddComponent<Transform>();
        }
        transform = &entity->GetComponent<Transform>();
    }

    void Label::Update()
    {
        if (mobile)
        {
            dstRect.x = transform->GetPos().x - PlayingState::camera.x;
            dstRect.y = transform->GetPos().y - PlayingState::camera.y - 10; // FIXME: offset magic number à retirer
        }
    }

    void Label::Render()
    {
        if (SDL_RenderCopy(Game::renderer, labelTexture, &srcRect, &dstRect) != 0)
        {
            std::cerr << "Erreur de render du text" << std::endl;
        }
    }

    void Label::SetLabelText()
    {
        SDL_Surface *surface = TTF_RenderText_Blended(Game::assets->GetFont(font), text.c_str(), color);
        if (surface == NULL)
        {
            std::cerr << "Erreur de render du text : " << SDL_GetError() << std::endl;
            return;
        }
        labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surface);
        if (labelTexture == NULL)
        {
            std::cerr << "Erreur de création de texture à partir du text : " << SDL_GetError() << std::endl;
            SDL_FreeSurface(surface);
            return;
        }
        int width, height;
        if (SDL_QueryTexture(labelTexture, nullptr, nullptr, &width, &height))
        {
            std::cerr << "Erreur de récupération des dimensions du text : " << SDL_GetError() << std::endl;
        }
        srcRect = {0, 0, width, height};
        SDL_FreeSurface(surface);
    }

}