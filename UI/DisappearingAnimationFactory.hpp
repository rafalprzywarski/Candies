#pragma once
#include "Position.hpp"
#include "Animation.hpp"
#include <memory>

namespace Candies
{
    namespace UI
    {
        class DisappearingAnimationFactory
        {
        public:
            virtual ~DisappearingAnimationFactory() { }
            virtual AnimationPtr createAnimation(const Positions& positions, const SpritesWithPositions& oldSprites) = 0;
        };
        
        typedef std::shared_ptr<DisappearingAnimationFactory> DisappearingAnimationFactoryPtr;
    }
}
