#include "AnimationsFactory.hpp"
#include <UI/SmoothFallingAnimation.hpp>
#include <UI/SmoothSwappingAnimation.hpp>
#include <UI/SmoothDisappearingAnimation.hpp>
#include <UI/ConstantVelocityTransitionAnimator.hpp>
#include <UI/ConstantTimeDisappearingAnimator.hpp>

namespace Candies
{
    namespace UI
    {
        AnimationPtr AnimationsFactory::createFallingAnimation(const SpritesWithPositions& newSprites, const SpritesWithPositions& oldSprites)
        {
            auto transitionAnimator = std::make_shared<ConstantVelocityTransitionAnimator>(timer, settings.fallingVelocity);
            return std::make_shared<SmoothFallingAnimation>(transitionAnimator, settings.initialFallingHeight, newSprites, oldSprites);
        }
        
        AnimationPtr AnimationsFactory::createSwappingAnimation(Position first, Position second, const SpritesWithPositions& oldSprites)
        {
            auto transitionAnimator = std::make_shared<ConstantVelocityTransitionAnimator>(timer, settings.swappingVelocity);
            return std::make_shared<SmoothSwappingAnimation>(transitionAnimator, first, second, oldSprites);
        }
        
        AnimationPtr AnimationsFactory::createDisappearingAnimation(const Positions& positions, const SpritesWithPositions& oldSprites)
        {
            auto disappearingAnimator = std::make_shared<ConstantTimeDisappearingAnimator>(timer, settings.disappearingTime);
            return std::make_shared<SmoothDisappearingAnimation>(disappearingAnimator, positions, oldSprites);
        }
    }
}
