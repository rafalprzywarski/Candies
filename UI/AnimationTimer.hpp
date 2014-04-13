#pragma once
#include <memory>

namespace Candies
{
    namespace UI
    {
        class AnimationTimer
        {
        public:
            virtual ~AnimationTimer() { }
            virtual float getTime() = 0;
        };
        
        typedef std::shared_ptr<AnimationTimer> AnimationTimerPtr;
    }
}
