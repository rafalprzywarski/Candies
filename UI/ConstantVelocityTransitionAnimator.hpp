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
            ConstantVelocityTransitionAnimator(AnimationTimerPtr timer)
            : timer(timer) { }
            void addTransition(Position first, Position second, SpritePtr sprite);
            void updateFrame();
            void drawFrame() const;
            bool isFinished() const;
        private:
            AnimationTimerPtr timer;
            Position first{0, 0};
            SpritePtr sprite;
        };
        
        typedef std::shared_ptr<TransitionAnimator> TransitionAnimatorPtr;
    }
}
