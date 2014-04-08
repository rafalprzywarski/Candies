#include "SDLRendererFactory.hpp"

namespace Candies
{
    namespace UI
    {
        std::shared_ptr<SDL_Renderer> SDLRendererFactory::createRenderer(int width, int height)
        {
            struct WithDeps
            {
                std::shared_ptr<SDL_Window> window;
                std::shared_ptr<SDL_Renderer> renderer;
                
                WithDeps(int width, int height)
                : window(SDL_CreateWindow("Candies", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN), SDL_DestroyWindow),
                renderer(SDL_CreateRenderer(&*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer) { }
            };
            auto complete = std::make_shared<WithDeps>(width, height);
            return std::shared_ptr<SDL_Renderer>(complete, &*complete->renderer);
        }
    }
}
