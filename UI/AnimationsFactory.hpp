#pragma once
#include <UI/FallingAnimationFactory.hpp>
#include <UI/SwappingAnimationFactory.hpp>
#include <UI/DisappearingAnimationFactory.hpp>
#include <UI/AnimationTimer.hpp>

namespace Candies
{
    namespace UI
    {
        struct AnimationSettings
        {
            float fallingVelocity = 100;
            float initialFallingHeight = 0;
            float swappingVelocity = 100;
            float disappearingTime = 1;
        };
        
        class AnimationsFactory : public UI::FallingAnimationFactory, public UI::SwappingAnimationFactory, public UI::DisappearingAnimationFactory
        {
        public:
            AnimationsFactory(AnimationTimerPtr timer, const AnimationSettings& settings) : timer(timer), settings(settings) { }
            AnimationPtr createFallingAnimation(const SpritesWithPositions& newSprites, const SpritesWithPositions& oldSprites);
            AnimationPtr createSwappingAnimation(Position first, Position second, const SpritesWithPositions& oldSprites);
            AnimationPtr createDisappearingAnimation(const Positions& positions, const SpritesWithPositions& oldSprites);
        private:
            AnimationTimerPtr timer;
            AnimationSettings settings;
        };
    }
}
