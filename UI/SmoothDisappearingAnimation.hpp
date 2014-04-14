#pragma once
#include "Animation.hpp"
#include "SpriteWithPosition.hpp"
#include "DisappearingAnimator.hpp"

namespace Candies
{
    namespace UI
    {
        class SmoothDisappearingAnimation : public Animation
        {
        public:
            SmoothDisappearingAnimation(DisappearingAnimatorPtr disappearingAnimator, const Positions& toRemove, const SpritesWithPositions& oldSprites);
            SpritesWithPositions getFinalSprites() const;
            void updateFrame();
            void drawFrame() const;
            bool isFinished() const;
        private:
            DisappearingAnimatorPtr disappearingAnimator;
            SpritesWithPositions finalSprites;
        };
    }
}
