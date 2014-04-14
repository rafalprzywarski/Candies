#include "SmoothSwappingAnimation.hpp"

namespace Candies
{
    namespace UI
    {
        SmoothSwappingAnimation::SmoothSwappingAnimation(TransitionAnimatorPtr transitionAnimator, Position first, Position second, const SpritesWithPositions& sprites)
        : transitionAnimator(transitionAnimator), finalSprites(sprites)
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
    }
}
