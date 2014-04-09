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
            {
                switch (event.type)
                {
                    case SDL_QUIT:
                        finished = true;
                        return;
                    case SDL_MOUSEBUTTONDOWN:
                        mouseEventListener->mouseDown({event.button.x, event.button.y});
                        break;
                }
            }
            
            frameUpdateListener->update();
        }
        
        bool SDLEventDispatcher::isFinished() const
        {
            return finished;
        }
        
    }
}
