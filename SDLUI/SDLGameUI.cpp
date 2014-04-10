#include "SDLGameUI.hpp"
#include "SDLSprite.hpp"
#include "ResourcePath.h"
#include <SDL2_image/SDL_image.h>

namespace Candies
{
    namespace UI
    {
        SDLGameUI::SDLGameUI(std::shared_ptr<SDL_Renderer> renderer, SpritePtr background, FrameUpdateListenerPtr board, LabelPtr timer)
        : renderer(renderer), background(background), board(board), timer(timer)
        {
        }
        
        void SDLGameUI::update()
        {
            SDL_RenderClear(&*renderer);
            background->drawAt({0, 0});
            board->update();
            timer->update();
            SDL_RenderPresent(&*renderer);
        }
    }
}
