#include "StagedBoardAnimator.hpp"

namespace Candies
{
    namespace UI
    {
        void StagedBoardAnimator::addFallingAnimation(const SpritesWithPositions& sprites)
        {
            createAnimation.push([=](const SpritesWithPositions& finalSprites) { return fallingAnimationFactory->createAnimation(sprites, finalSprites); });
        }
        
        void StagedBoardAnimator::addSwappingAnimation(const Position& first, const Position& second)
        {
            createAnimation.push([=](const SpritesWithPositions& finalSprites) { return swappingAnimationFactory->createAnimation(first, second, finalSprites); });
        }

        void StagedBoardAnimator::updateFrame()
        {
            if (!shouldCreateNewAnimation())
                return;
            createNewAnimation();
        }
        
        void StagedBoardAnimator::drawFrame() const
        {
            if (animation)
                animation->drawFrame();
        }
        
        bool StagedBoardAnimator::shouldCreateNewAnimation() const
        {
            return (!animation || animation->isFinished()) && !createAnimation.empty();
        }
        
        void StagedBoardAnimator::createNewAnimation()
        {
            SpritesWithPositions finalSprites;
            if (animation)
                finalSprites = animation->getFinalSprites();
            animation = createAnimation.front()(finalSprites);
            createAnimation.pop();
        }
    }
}
