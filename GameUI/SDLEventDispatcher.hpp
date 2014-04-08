#pragma once
#include <GameUI/EventDispatcher.hpp>
#include <GameUI/FrameUpdateListener.hpp>

namespace Candies
{
    namespace UI
    {
        class SDLEventDispatcher : public EventDispatcher
        {
        public:
            SDLEventDispatcher(FrameUpdateListenerPtr frameUpdateListener) : frameUpdateListener(frameUpdateListener) { }
            virtual void dispatch();
            virtual bool isFinished() const;
        private:
            bool finished = false;
            FrameUpdateListenerPtr frameUpdateListener;
        };
    }
}