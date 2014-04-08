#include "SDLGameUI.hpp"
#include "SDLSprite.hpp"
#include "ResourcePath.h"
#include <SDL2_image/SDL_image.h>

namespace Candies
{
    namespace UI
    {
        namespace
        {
            auto const SCREEN_WIDTH = 755, SCREEN_HEIGHT = 600;
        }
        
        SDLGameUI::SDLGameUI()
        : window(SDL_CreateWindow("Candies", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN), SDL_DestroyWindow),
        renderer(SDL_CreateRenderer(&*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer),
        background(std::make_shared<SDLSprite>(renderer, "BackGround.jpg"))
        {
        }
        
        void SDLGameUI::update()
        {
            SDL_RenderClear(&*renderer);
            background->drawAt({0, 0});
            SDL_RenderPresent(&*renderer);
        }
    }
}
