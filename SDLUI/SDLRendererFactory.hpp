#pragma once
#include <SDL2/SDL.h>
#include <memory>

namespace Candies
{
    namespace UI
    {
        class SDLRendererFactory
        {
        public:
            std::shared_ptr<SDL_Renderer> createRenderer(int width, int height);
        };
    }
}
