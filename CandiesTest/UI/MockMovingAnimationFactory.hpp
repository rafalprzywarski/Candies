#pragma once
#include <UI/MovingAnimationFactory.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockMovingAnimationFactory : MovingAnimationFactory
        {
            MOCK_METHOD2(createMovingAnimation, AnimationPtr(const SpriteMovements&, const SpritesWithPositions&));
        };
        
        typedef std::shared_ptr<MockMovingAnimationFactory> MockMovingAnimationFactoryPtr;
    }
}
