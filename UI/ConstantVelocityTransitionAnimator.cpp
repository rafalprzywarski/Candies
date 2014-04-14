#include "ConstantVelocityTransitionAnimator.hpp"

namespace Candies
{
    namespace UI
    {
        void ConstantVelocityTransitionAnimator::addTransition(Position first, Position second, SpritePtr sprite)
        {
            this->first = first;
            this->sprite = sprite;
        }
        
        void ConstantVelocityTransitionAnimator::updateFrame()
        {
            
        }
        
        void ConstantVelocityTransitionAnimator::drawFrame() const
        {
            sprite->drawAt(first);
        }
        
        bool ConstantVelocityTransitionAnimator::isFinished() const
        {
            return false;
        }
    }
}
