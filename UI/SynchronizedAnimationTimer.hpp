#pragma once
#include "AnimationTimer.hpp"
#include "UpdateFrameListener.hpp"
#include <chrono>

namespace Candies
{
    namespace UI
    {
        class SynchronizedAnimationTimer : public AnimationTimer, public UpdateFrameListener
        {
        public:
            SynchronizedAnimationTimer();
            float getTime() const;
            void updateFrame();
        private:
            std::chrono::high_resolution_clock::time_point start, now;
        };
    }
}
