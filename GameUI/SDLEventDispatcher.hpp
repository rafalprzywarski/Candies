#pragma once
#include <GameUI/EventDispatcher.hpp>
#include <GameUI/FrameUpdateListener.hpp>
#include <GameUI/MouseEventListener.hpp>

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