#include "SDLGameUI.hpp"
#include "SDLSprite.hpp"
#include "ResourcePath.h"
#include <SDL2_image/SDL_image.h>

namespace Candies
{
    namespace UI
    {
        SDLGameUI::SDLGameUI(std::shared_ptr<SDL_Renderer> renderer, DrawFrameListeners drawListeners)
        : renderer(renderer), drawListeners(drawListeners)
        {
        }
        
        void SDLGameUI::drawFrame() const
        {
            SDL_RenderClear(&*renderer);
            for (auto& l : drawListeners)
                l->drawFrame();
            SDL_RenderPresent(&*renderer);
        }
    }
}
