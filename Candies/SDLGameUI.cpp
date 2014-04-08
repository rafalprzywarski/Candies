#include "SDLGameUI.hpp"
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
        renderer(SDL_CreateRenderer(&*window, -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer),
        background(IMG_LoadTexture(&*renderer, getResourcePath("BackGround.jpg").c_str()), SDL_DestroyTexture)
        {
        }
        
        void SDLGameUI::update()
        {
            SDL_RenderClear(&*renderer);
            SDL_RenderCopy(&*renderer, &*background, nullptr, nullptr);
            SDL_RenderPresent(&*renderer);
        }
    }
}
