#pragma once
#include <UI/AnimationTimer.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockAnimationTimer : AnimationTimer
        {
            MOCK_METHOD0(getTime, float());
        };
        
        typedef std::shared_ptr<MockAnimationTimer> MockAnimationTimerPtr;
    }
}
