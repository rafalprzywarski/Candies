#include "SDLLabel.hpp"
#include "ResourcePath.h"

namespace Candies
{
    namespace UI
    {
        SDLLabel::SDLLabel(std::shared_ptr<SDL_Renderer> renderer, const std::string& fontFile, int fontHeight, SDL_Color color, Position position)
        : renderer(renderer), font(TTF_OpenFont(getResourcePath(fontFile).c_str(), fontHeight), TTF_CloseFont), color(color), position(position)
        {
            if (!font)
                throw FontLoadError(fontFile, TTF_GetError());
            setText({});
        }
        
        void SDLLabel::update()
        {
            SDL_Rect target{};
            target.x = position.x;
            target.y = position.y;
            SDL_QueryTexture(&*texture, nullptr, nullptr, &target.w, &target.h);
            SDL_RenderCopy(&*renderer, &*texture, nullptr, &target);
        }
        
        void SDLLabel::setText(const std::string& text)
        {
            std::shared_ptr<SDL_Surface> surface(TTF_RenderText_Blended(&*font, text.c_str(), color), SDL_FreeSurface);
            texture.reset(SDL_CreateTextureFromSurface(&*renderer, surface.get()), SDL_DestroyTexture);
        }

    }
}
