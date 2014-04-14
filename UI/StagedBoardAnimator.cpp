#include "StagedBoardAnimator.hpp"

namespace Candies
{
    namespace UI
    {
        void StagedBoardAnimator::addFallingAnimation(const SpritesWithPositions& sprites)
        {
            this->sprites = sprites;
        }
        
        void StagedBoardAnimator::updateFrame()
        {
            animation = fallingAnimationFactory->createAnimation(sprites, {});
        }
        
        void StagedBoardAnimator::drawFrame() const
        {
            animation->drawFrame();
        }
    }
}
