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
            MOCK_METHOD2(destroySpriteAt, void(SpritePtr sprite, Position at));
            MOCK_CONST_METHOD0(draw, void());
        };
        
        typedef std::shared_ptr<MockSpriteAnimator> MockSpriteAnimatorPtr;
    }
}
