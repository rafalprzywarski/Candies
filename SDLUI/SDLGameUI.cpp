#include "SDLGameUI.hpp"
#include "SDLSprite.hpp"
#include "ResourcePath.h"
#include <SDL2_image/SDL_image.h>

namespace Candies
{
    namespace UI
    {
        SDLGameUI::SDLGameUI(std::shared_ptr<SDL_Renderer> renderer, SpritePtr background, FrameUpdateListenerPtr board)
        : renderer(renderer), background(background), board(board)
        {
        }
        
        void SDLGameUI::update()
        {
            SDL_RenderClear(&*renderer);
            background->drawAt({0, 0});
            board->update();
            SDL_RenderPresent(&*renderer);
        }
    }
}
