#pragma once
#include <UI/FallingAnimationFactory.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockFallingAnimationFactory : FallingAnimationFactory
        {
            MOCK_METHOD2(createFallingAnimation, AnimationPtr(const SpritesWithPositions&, const SpritesWithPositions&));
        };
        
        typedef std::shared_ptr<MockFallingAnimationFactory> MockFallingAnimationFactoryPtr;
    }
}
