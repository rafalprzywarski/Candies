#pragma once
#include <UI/TimedInterpolator.hpp>
#include <gmock/gmock.h>
#include <memory>

namespace Candies
{
    namespace UI
    {
        struct MockTimedInterpolator : TimedInterpolator
        {
            MOCK_CONST_METHOD3(interpolate, int(int from, int to, float time));
        };
        
        typedef std::shared_ptr<MockTimedInterpolator> MockTimedInterpolatorPtr;
    }
}
