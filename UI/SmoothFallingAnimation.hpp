#pragma once
#include "Animation.hpp"
#include "SpriteWithPosition.hpp"
#include "TransitionAnimator.hpp"

namespace Candies
{
    namespace UI
    {
        class SmoothFallingAnimation : public Animation
        {
        public:
            SmoothFallingAnimation(TransitionAnimatorPtr transitionAnimator, int initialHeight, const SpritesWithPositions& newSprites, const SpritesWithPositions& oldSprites);
            SpritesWithPositions getFinalSprites() const;
            void updateFrame();
            void drawFrame() const;
            bool isFinished() const;
        private:
            TransitionAnimatorPtr transitionAnimator;
            int initialHeight;
            SpritesWithPositions newSprites, oldSprites;
            int getLowestYFromNewSprites() const;
        };
    }
}
