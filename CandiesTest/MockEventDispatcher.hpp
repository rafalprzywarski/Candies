#pragma once
#include <UI/EventDispatcher.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockEventDispatcher : EventDispatcher
        {
            MOCK_METHOD0(dispatch, void());
            MOCK_CONST_METHOD0(isFinished, bool());
        };
        
        typedef std::shared_ptr<MockEventDispatcher> MockEventDispatcherPtr;
    }
}
