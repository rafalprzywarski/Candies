#pragma once
#include <UI/SpriteAnimator.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockSpriteAnimator : SpriteAnimator
        {
            MOCK_METHOD3(moveSprite, void(SpritePtr sprite, Position from, Position to));
            MOCK_METHOD1(destroySpriteAt, void(Position at));
            MOCK_CONST_METHOD0(isAnimating, bool());
            MOCK_CONST_METHOD0(draw, void());
        };
        
        typedef std::shared_ptr<MockSpriteAnimator> MockSpriteAnimatorPtr;
    }
}
