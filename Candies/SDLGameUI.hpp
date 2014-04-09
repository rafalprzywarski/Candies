#pragma once
#include <UI/FrameUpdateListener.hpp>
#include <UI/Sprite.hpp>
#include <SDL2/SDL.h>

namespace Candies
{
    namespace UI
    {
        class SDLGameUI : public FrameUpdateListener
        {
        public:
            SDLGameUI(std::shared_ptr<SDL_Renderer> renderer, SpritePtr background, FrameUpdateListenerPtr board);
            void update();
        private:
            std::shared_ptr<SDL_Renderer> renderer;
            SpritePtr background;
            FrameUpdateListenerPtr board;
        };
    }
}
