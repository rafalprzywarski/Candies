#pragma once
#include <UI/EventDispatcher.hpp>
#include <UI/FrameUpdateListener.hpp>
#include <UI/MouseEventListener.hpp>
#include <vector>

namespace Candies
{
    namespace UI
    {
        typedef std::vector<FrameUpdateListenerPtr> FrameUpdateListeners;

        class SDLEventDispatcher : public EventDispatcher
        {
        public:
            SDLEventDispatcher(FrameUpdateListeners frameUpdateListeners, MouseEventListenerPtr mouseEventListener)
            : frameUpdateListeners(frameUpdateListeners), mouseEventListener(mouseEventListener) { }
            virtual void dispatch();
            virtual bool isFinished() const;
        private:
            bool finished = false;
            FrameUpdateListeners frameUpdateListeners;
            MouseEventListenerPtr mouseEventListener;
        };
    }
}
