#pragma once
#include <UI/Sprite.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockSprite : Sprite
        {
            MOCK_METHOD1(drawAt, void(Position));
            MOCK_METHOD2(drawWithAlphaAt, void(float, Position));
        };
        
        typedef std::shared_ptr<MockSprite> MockSpritePtr;
    }
}
