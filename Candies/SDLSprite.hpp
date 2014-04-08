#pragma once
#include <GameUI/Sprite.hpp>
#include <SDL2/SDL.h>

namespace Candies
{
    namespace UI
    {
        class SDLSprite : public Sprite
        {
        public:
            SDLSprite(std::shared_ptr<SDL_Renderer> renderer, const std::string& filename);
            virtual void drawAt(Position p);
        private:
            std::shared_ptr<SDL_Renderer> renderer;
            std::shared_ptr<SDL_Texture> texture;
        };
    }
}
