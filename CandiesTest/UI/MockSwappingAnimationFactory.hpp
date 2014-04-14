#pragma once
#include <UI/SwappingAnimationFactory.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockSwappingAnimationFactory : SwappingAnimationFactory
        {
            MOCK_METHOD3(createAnimation, AnimationPtr(Position first, Position second, const SpritesWithPositions&));
        };
        
        typedef std::shared_ptr<MockSwappingAnimationFactory> MockSwappingAnimationFactoryPtr;
    }
}
