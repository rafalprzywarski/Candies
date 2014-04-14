#pragma once
#include "Animation.hpp"
#include "SpriteWithPosition.hpp"
#include "TransitionAnimator.hpp"

namespace Candies
{
    namespace UI
    {
        class SmoothSwappingAnimation
        {
        public:
            SmoothSwappingAnimation(TransitionAnimatorPtr transitionAnimator, Position first, Position second, const SpritesWithPositions& sprites);
            SpritesWithPositions getFinalSprites() const;
            void updateFrame();
        private:
            TransitionAnimatorPtr transitionAnimator;
            SpritesWithPositions finalSprites;
        };
    }
}
