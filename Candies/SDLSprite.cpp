#include "SDLSprite.hpp"
#include "ResourcePath.h"
#include <SDL2_image/SDL_image.h>

namespace Candies
{
    namespace UI
    {
        SDLSprite::SDLSprite(std::shared_ptr<SDL_Renderer> renderer, const std::string& filename)
        : renderer(renderer),
        texture(IMG_LoadTexture(&*renderer, getResourcePath(filename).c_str()), SDL_DestroyTexture)
        {
        }

        void SDLSprite::drawAt(Position p)
        {
            SDL_Rect target{};
            target.x = p.x;
            target.y = p.y;
            SDL_QueryTexture(&*texture, nullptr, nullptr, &target.w, &target.h);
            SDL_RenderCopy(&*renderer, &*texture, nullptr, &target);
        }
    }
}
