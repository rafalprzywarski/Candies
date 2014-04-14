#include "StagedBoardAnimator.hpp"

namespace Candies
{
    namespace UI
    {
        void StagedBoardAnimator::addFallingAnimation(const SpritesWithPositions& sprites)
        {
            createAnimation.push([=]() { return fallingAnimationFactory->createAnimation(sprites, {}); });
        }
        
        void StagedBoardAnimator::addSwappingAnimation(const Position& first, const Position& second)
        {
            createAnimation.push([=]() { return swappingAnimationFactory->createAnimation(first, second, {}); });
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
            animation = createAnimation.front()();
            createAnimation.pop();
        }
    }
}
