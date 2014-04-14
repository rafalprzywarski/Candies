#pragma once
#include "Animation.hpp"
#include "SpriteMovement.hpp"
#include "TransitionAnimator.hpp"
#include <unordered_map>

namespace Candies
{
    namespace UI
    {
        class SmoothMovingAnimation : public Animation
        {
        public:
            SmoothMovingAnimation(TransitionAnimatorPtr transitionAnimator, const SpriteMovements& movements, const SpritesWithPositions& oldSprites);
            SpritesWithPositions getFinalSprites() const;
            void updateFrame();
            void drawFrame() const;
            bool isFinished() const;
        private:
            typedef std::unordered_map<Position, Position> Transitions;
            TransitionAnimatorPtr transitionAnimator;
            SpritesWithPositions movingSprites, staticSprites;
            
            Transitions createMovementTransitions(const SpriteMovements& movements);
            void addTransitions(const Transitions& transitions, const SpritesWithPositions& oldSprites);
        };
    }
}
