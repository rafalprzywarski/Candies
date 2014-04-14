#include "StagedBoardAnimator.hpp"

namespace Candies
{
    namespace UI
    {
        void StagedBoardAnimator::addFallingAnimation(const SpritesWithPositions& sprites)
        {
            createAnimation.push([=](const SpritesWithPositions& finalSprites) { return fallingAnimationFactory->createFallingAnimation(sprites, finalSprites); });
        }
        
        void StagedBoardAnimator::addMovingAnimation(const SpriteMovements& movements)
        {
            createAnimation.push([=](const SpritesWithPositions& finalSprites) { return movingAnimationFactory->createMovingAnimation(movements, finalSprites); });
        }

        void StagedBoardAnimator::addSwappingAnimation(const Position& first, const Position& second)
        {
            createAnimation.push([=](const SpritesWithPositions& finalSprites) { return swappingAnimationFactory->createSwappingAnimation(first, second, finalSprites); });
        }
        
        void StagedBoardAnimator::addDisappearingAnimation(const Positions& positions)
        {
            createAnimation.push([=](const SpritesWithPositions& finalSprites) { return disappearingAnimationFactory->createDisappearingAnimation(positions, finalSprites); });
        }

        void StagedBoardAnimator::updateFrame()
        {
            if (animation)
                animation->updateFrame();
            if (!shouldCreateNewAnimation())
                return;
            createNewAnimation();
        }
        
        void StagedBoardAnimator::drawFrame() const
        {
            if (animation)
                animation->drawFrame();
        }
        
        bool StagedBoardAnimator::isFinished() const
        {
            return createAnimation.empty() && (!animation || animation->isFinished());
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
