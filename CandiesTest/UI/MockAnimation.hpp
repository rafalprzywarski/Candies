#pragma once
#include <UI/Animation.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockAnimation : Animation
        {
            MOCK_METHOD0(updateFrame, void());
            MOCK_CONST_METHOD0(drawFrame, void());
            MOCK_CONST_METHOD0(isFinished, bool());
            MOCK_CONST_METHOD0(getFinalSprites, SpritesWithPositions());
        };
        
        typedef std::shared_ptr<MockAnimation> MockAnimationPtr;
    }
}
