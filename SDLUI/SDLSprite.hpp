#pragma once
#include <UI/Sprite.hpp>
#include <SDL2/SDL.h>

namespace Candies
{
    namespace UI
    {
        class SpriteNotFound : public std::runtime_error
        {
        public:
            SpriteNotFound(const std::string& filename) : std::runtime_error("Sprite not found " + filename) { }
        };
        
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
