#pragma once
#include "FallingAnimationFactory.hpp"
#include "SpriteWithPosition.hpp"

namespace Candies
{
    namespace UI
    {
        class StagedBoardAnimator
        {
        public:
            StagedBoardAnimator(FallingAnimationFactoryPtr fallingAnimationFactory)
            : fallingAnimationFactory(fallingAnimationFactory) { }
            void addFallingAnimation(const SpritesWithPositions& sprites);
            void updateFrame();
            void drawFrame() const;
        private:
            FallingAnimationFactoryPtr fallingAnimationFactory;
            SpritesWithPositions sprites;
            AnimationPtr animation;
        };
    }
}
