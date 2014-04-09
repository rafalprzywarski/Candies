#pragma once
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockSprite : Sprite
        {
            MOCK_METHOD1(drawAt, void(Position));
        };
        
        typedef std::shared_ptr<MockSprite> MockSpritePtr;
    }
}
