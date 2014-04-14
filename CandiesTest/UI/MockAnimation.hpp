#pragma once
#include <UI/Animation.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockAnimation : Animation
        {
            MOCK_CONST_METHOD0(drawFrame, void());
        };
        
        typedef std::shared_ptr<MockAnimation> MockAnimationPtr;
    }
}