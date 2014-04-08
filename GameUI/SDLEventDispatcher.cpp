#include "SDLEventDispatcher.hpp"
#include <SDL2/SDL.h>

namespace Candies
{
    namespace UI
    {
        void SDLEventDispatcher::dispatch()
        {
            SDL_Event event{};
            while (SDL_PollEvent(&event))
                if (event.type == SDL_QUIT)
                {
                    finished = true;
                    return;
                }
            frameUpdateListener->update();
        }
        
        bool SDLEventDispatcher::isFinished() const
        {
            return finished;
        }
        
    }
}