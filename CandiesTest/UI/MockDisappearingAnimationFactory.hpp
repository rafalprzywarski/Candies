#pragma once
#include <UI/DisappearingAnimationFactory.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockDisappearingAnimationFactory : DisappearingAnimationFactory
        {
            MOCK_METHOD2(createDisappearingAnimation, AnimationPtr(const Positions& positions, const SpritesWithPositions&));
        };
        
        typedef std::shared_ptr<MockDisappearingAnimationFactory> MockDisappearingAnimationFactoryPtr;
    }
}
