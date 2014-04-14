#pragma once
#include "TransitionAnimator.hpp"
#include "AnimationTimer.hpp"

namespace Candies
{
    namespace UI
    {
        class ConstantVelocityTransitionAnimator : public TransitionAnimator
        {
        public:
            ConstantVelocityTransitionAnimator(AnimationTimerPtr timer, float velocity)
            : timer(timer), velocity(velocity) { }
            void addTransition(Position first, Position second, SpritePtr sprite);
            void updateFrame();
            void drawFrame() const;
            bool isFinished() const;
        private:
            float velocity;
            AnimationTimerPtr timer;
            Position first{0, 0}, second{0, 0}, position{0, 0};
            float startTime{0};
            SpritePtr sprite;
            static int lerp(int from, int to, float t);
            static Position lerp(Position from, Position to, float t);
            static float distance(Position from, Position to);
        };
        
        typedef std::shared_ptr<TransitionAnimator> TransitionAnimatorPtr;
    }
}
