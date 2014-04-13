#pragma once
#include <UI/EventDispatcher.hpp>
#include <UI/UpdateFrameListener.hpp>
#include <UI/MouseEventListener.hpp>
#include <SDLUI/SDLGameUI.hpp>
#include <vector>

namespace Candies
{
    namespace UI
    {
        typedef std::vector<UpdateFrameListenerPtr> UpdateFrameListeners;

        class SDLEventDispatcher : public EventDispatcher
        {
        public:
            SDLEventDispatcher(UpdateFrameListeners updateFrameListeners, SDLGameUIPtr gameUI, MouseEventListenerPtr mouseEventListener)
            : updateFrameListeners(updateFrameListeners), gameUI(gameUI), mouseEventListener(mouseEventListener) { }
            virtual void dispatch();
            virtual bool isFinished() const;
        private:
            bool finished = false;
            UpdateFrameListeners updateFrameListeners;
            SDLGameUIPtr gameUI;
            MouseEventListenerPtr mouseEventListener;
        };
    }
}
