#pragma once
#include <UI/Switch.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockSwitch : Switch
        {
            MOCK_METHOD0(disable, void());
        };
        
        typedef std::shared_ptr<MockSwitch> MockSwitchPtr;
    }
}
