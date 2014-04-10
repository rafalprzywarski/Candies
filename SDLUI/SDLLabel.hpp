#pragma once
#include <UI/Label.hpp>
#include <UI/Position.hpp>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

namespace Candies
{
    namespace UI
    {
        class FontNotFound : public std::runtime_error
        {
        public:
            FontNotFound(const std::string& filename) : std::runtime_error("Font not found " + filename) { }
        };

        class SDLLabel : public Label
        {
        public:
            SDLLabel(std::shared_ptr<SDL_Renderer> renderer, const std::string& fontFile, int fontHeight, SDL_Color color, Position position);
            virtual void update();
            virtual void setText(const std::string& text);
        private:
            std::shared_ptr<TTF_Font> font;
            std::shared_ptr<SDL_Renderer> renderer;
            std::shared_ptr<SDL_Texture> texture;
            SDL_Color color;
            Position position;
        };
    }
}
