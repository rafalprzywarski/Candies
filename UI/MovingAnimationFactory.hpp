#pragma once
#include "SpriteMovement.hpp"
#include "Animation.hpp"
#include <memory>

namespace Candies
{
    namespace UI
    {
        class MovingAnimationFactory
        {
        public:
            virtual ~MovingAnimationFactory() { }
            virtual AnimationPtr createMovingAnimation(const SpriteMovements& movements, const SpritesWithPositions& oldSprites) = 0;
        };
        
        typedef std::shared_ptr<MovingAnimationFactory> MovingAnimationFactoryPtr;
    }
}
