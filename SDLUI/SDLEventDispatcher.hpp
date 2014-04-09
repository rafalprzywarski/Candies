#pragma once
#include <UI/EventDispatcher.hpp>
#include <UI/FrameUpdateListener.hpp>
#include <UI/MouseEventListener.hpp>

namespace Candies
{
    namespace UI
    {
        class SDLEventDispatcher : public EventDispatcher
        {
        public:
            SDLEventDispatcher(FrameUpdateListenerPtr frameUpdateListener, MouseEventListenerPtr mouseEventListener)
            : frameUpdateListener(frameUpdateListener), mouseEventListener(mouseEventListener) { }
            virtual void dispatch();
            virtual bool isFinished() const;
        private:
            bool finished = false;
            FrameUpdateListenerPtr frameUpdateListener;
            MouseEventListenerPtr mouseEventListener;
        };
    }
}
