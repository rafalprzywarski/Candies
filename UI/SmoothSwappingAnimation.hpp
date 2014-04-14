#pragma once
#include "Animation.hpp"
#include "SpriteWithPosition.hpp"
#include "TransitionAnimator.hpp"

namespace Candies
{
    namespace UI
    {
        class SmoothSwappingAnimation : public Animation
        {
        public:
            SmoothSwappingAnimation(TransitionAnimatorPtr transitionAnimator, Position first, Position second, const SpritesWithPositions& sprites);
            SpritesWithPositions getFinalSprites() const;
            void updateFrame();
            void drawFrame() const;
            bool isFinished() const;
        private:
            TransitionAnimatorPtr transitionAnimator;
            Position first, second;
            SpritesWithPositions finalSprites;
        };
    }
}
