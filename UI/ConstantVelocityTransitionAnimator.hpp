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
            struct Transition
            {
                Position first, second, position;
                float startTime;
                SpritePtr sprite;

                Transition(Position first, Position second, float startTime, SpritePtr sprite)
                : first(first), second(second), position(first), startTime(startTime), sprite(sprite) { }
                void update(float time, float velocity);
                void draw() const;
                bool isFinished() const { return position == second; }
            };
            
            float velocity;
            AnimationTimerPtr timer;
            std::vector<Transition> transitions;
            
            static int lerp(int from, int to, float t);
            static Position lerp(Position from, Position to, float t);
            static float distance(Position from, Position to);
        };
        
        typedef std::shared_ptr<TransitionAnimator> TransitionAnimatorPtr;
    }
}
