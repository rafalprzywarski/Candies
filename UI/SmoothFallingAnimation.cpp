#include "SmoothFallingAnimation.hpp"

namespace Candies
{
    namespace UI
    {
        SmoothFallingAnimation::SmoothFallingAnimation(TransitionAnimatorPtr transitionAnimator, int initialHeight, const SpritesWithPositions& newSprites, const SpritesWithPositions& oldSprites)
        : transitionAnimator(transitionAnimator), initialHeight(initialHeight), newSprites(newSprites), oldSprites(oldSprites)
        {
            auto lowestY = getLowestYFromNewSprites();
            for (auto const& s : newSprites)
                transitionAnimator->addTransition({s.position.x, s.position.y - lowestY + initialHeight}, s.position, s.sprite);
        }
        
        SpritesWithPositions SmoothFallingAnimation::getFinalSprites() const
        {
            auto finalSprites = oldSprites;
            finalSprites.insert(finalSprites.end(), newSprites.begin(), newSprites.end());
            return finalSprites;
        }
        
        void SmoothFallingAnimation::updateFrame()
        {
            transitionAnimator->updateFrame();
        }
        
        void SmoothFallingAnimation::drawFrame() const
        {
            transitionAnimator->drawFrame();
            for (auto& s : oldSprites)
                s.sprite->drawAt(s.position);
        }
        
        bool SmoothFallingAnimation::isFinished() const
        {
            return transitionAnimator->isFinished();
        }
        
        int SmoothFallingAnimation::getLowestYFromNewSprites() const
        {
            if (newSprites.empty())
                throw std::invalid_argument("SmoothFallingAnimation given no new sprites");
            return std::min_element(newSprites.begin(), newSprites.end(), [](const SpriteWithPosition& left, const SpriteWithPosition& right)
            {
                return left.position.y > right.position.y;
            })->position.y;
        }
    }
}
