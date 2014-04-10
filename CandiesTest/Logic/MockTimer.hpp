#pragma once
#include <Logic/Timer.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace Logic
    {
        struct MockTimer : Timer
        {
            MOCK_METHOD0(start, void());
            MOCK_CONST_METHOD0(getTime, int());
        };
        
        typedef std::shared_ptr<MockTimer> MockTimerPtr;
    }
}
