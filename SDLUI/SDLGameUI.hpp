#pragma once
#include <UI/DrawFrameListener.hpp>
#include <SDL2/SDL.h>
#include <vector>

namespace Candies
{
    namespace UI
    {
        typedef std::vector<DrawFrameListenerPtr> DrawFrameListeners;

        class SDLGameUI : public DrawFrameListener
        {
        public:
            SDLGameUI(std::shared_ptr<SDL_Renderer> renderer, DrawFrameListeners drawListeners);
            void drawFrame() const;
        private:
            std::shared_ptr<SDL_Renderer> renderer;
            DrawFrameListeners drawListeners;
        };
        
        typedef std::shared_ptr<SDLGameUI> SDLGameUIPtr;
    }
}
