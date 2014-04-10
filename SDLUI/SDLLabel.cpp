#include "SDLLabel.hpp"
#include "ResourcePath.h"

namespace Candies
{
    namespace UI
    {
        SDLLabel::SDLLabel(std::shared_ptr<SDL_Renderer> renderer, const std::string& fontFile, int fontHeight, Position position)
        : renderer(renderer), font(TTF_OpenFont(getResourcePath(fontFile).c_str(), fontHeight), TTF_CloseFont), position(position)
        {
            if (!font)
                throw FontNotFound(fontFile);
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
            SDL_Color color = {220, 245, 255};
            std::shared_ptr<SDL_Surface> surface(TTF_RenderText_Blended(&*font, text.c_str(), color), SDL_FreeSurface);
            texture.reset(SDL_CreateTextureFromSurface(&*renderer, surface.get()), SDL_DestroyTexture);
        }

    }
}
