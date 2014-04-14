#include "StagedBoardAnimator.hpp"

namespace Candies
{
    namespace UI
    {
        void StagedBoardAnimator::addFallingAnimation(const SpritesWithPositions& sprites)
        {
            createAnimation = [=]() { return fallingAnimationFactory->createAnimation(sprites, {}); };
        }
        
        void StagedBoardAnimator::addSwappingAnimation(const Position& first, const Position& second)
        {
            createAnimation = [=]() { return swappingAnimationFactory->createAnimation(first, second, {}); };
        }

        void StagedBoardAnimator::updateFrame()
        {
            if (createAnimation)
                animation = createAnimation();
        }
        
        void StagedBoardAnimator::drawFrame() const
        {
            if (animation)
            animation->drawFrame();
        }
    }
}
