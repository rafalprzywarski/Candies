#pragma once
#include "EventDispatcher.hpp"
#include <SDL2/SDL.h>

namespace Candies
{
    namespace UI
    {
        class SDLGameUI
        {
        public:
            SDLGameUI();
            void update();
        private:
            std::shared_ptr<SDL_Window> window;
            std::shared_ptr<SDL_Renderer> renderer;
            std::shared_ptr<SDL_Texture> background;
        };
    }
}
