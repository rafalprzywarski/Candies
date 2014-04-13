#pragma once
#include "SpriteAnimator.hpp"
#include "UpdateFrameListener.hpp"
#include "AnimationTimer.hpp"
#include <memory>

namespace Candies
{
    namespace UI
    {
        class LinearSpriteAnimator : public SpriteAnimator, public UpdateFrameListener
        {
        public:
            LinearSpriteAnimator(AnimationTimerPtr timer, float animationTime)
            : timer(timer), animationTime(animationTime) { }
            void moveSprite(SpritePtr sprite, Position from, Position to);
            void destroySpriteAt(SpritePtr sprite, Position at);
            bool isAnimating() const;
            void draw() const;
            void updateFrame();
        private:
            AnimationTimerPtr timer;
            float animationTime;
            SpritePtr sprite;
            Position from{0, 0}, to{0, 0}, position{0, 0};
            float startTime{0};
            
            static int lerp(int from, int to, float t);
            static Position lerp(Position from, Position to, float t);
        };
    }
}
