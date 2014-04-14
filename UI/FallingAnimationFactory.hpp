#pragma once
#include "SpriteWithPosition.hpp"
#include "Animation.hpp"
#include <memory>

namespace Candies
{
    namespace UI
    {
        class FallingAnimationFactory
        {
        public:
            virtual ~FallingAnimationFactory() { }
            virtual AnimationPtr createFallingAnimation(const SpritesWithPositions& newSprites, const SpritesWithPositions& oldSprites) = 0;
        };
        
        typedef std::shared_ptr<FallingAnimationFactory> FallingAnimationFactoryPtr;
    }
}
