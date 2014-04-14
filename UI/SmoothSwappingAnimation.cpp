#include "SmoothSwappingAnimation.hpp"

namespace Candies
{
    namespace UI
    {
        SmoothSwappingAnimation::SmoothSwappingAnimation(TransitionAnimatorPtr transitionAnimator, Position first, Position second, const SpritesWithPositions& sprites)
        : transitionAnimator(transitionAnimator), first(first), second(second), finalSprites(sprites)
        {
            SpritePtr firstSprite, secondSprite;
            for (auto& s : finalSprites)
                if (s.position == first)
                {
                    firstSprite = s.sprite;
                    s.position = second;
                }
                else if (s.position == second)
                {
                    secondSprite = s.sprite;
                    s.position = first;
                }
            transitionAnimator->addTransition(first, second, firstSprite);
            transitionAnimator->addTransition(second, first, secondSprite);
        }
        
        SpritesWithPositions SmoothSwappingAnimation::getFinalSprites() const
        {
            return finalSprites;
        }
        
        void SmoothSwappingAnimation::updateFrame()
        {
            transitionAnimator->updateFrame();
        }

        void SmoothSwappingAnimation::drawFrame() const
        {
            transitionAnimator->drawFrame();
            for (auto& s : finalSprites)
                if (s.position != first && s.position != second)
                    s.sprite->drawAt(s.position);
        }

        bool SmoothSwappingAnimation::isFinished() const
        {
            return transitionAnimator->isFinished();
        }
    }
}
