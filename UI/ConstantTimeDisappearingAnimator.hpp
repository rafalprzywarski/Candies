#pragma once
#include "DisappearingAnimator.hpp"
#include "AnimationTimer.hpp"
#include "SpriteWithPosition.hpp"

namespace Candies
{
    namespace UI
    {
        class ConstantTimeDisappearingAnimator : public DisappearingAnimator
        {
        public:
            ConstantTimeDisappearingAnimator(AnimationTimerPtr time, float animationTime);
            void addDisappearing(Position pos, SpritePtr sprite);
            void updateFrame();
            void drawFrame() const;
            bool isFinished() const;
        private:
            SpritesWithPositions sprites;
            AnimationTimerPtr timer;
            float animationTime, startTime, currentTime;

            float calculateAlpha() const;
        };
    }
}
