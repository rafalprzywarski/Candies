#include "LinearSpriteAnimator.hpp"

namespace Candies
{
    namespace UI
    {
        void LinearSpriteAnimator::moveSprite(SpritePtr sprite, Position from, Position to)
        {
            this->sprite = sprite;
            this->position = from;
            this->to = to;
        }
        
        void LinearSpriteAnimator::destroySpriteAt(SpritePtr sprite, Position at)
        {
        }
        
        bool LinearSpriteAnimator::isAnimating() const
        {
            return false;
        }
        
        void LinearSpriteAnimator::draw() const
        {
            sprite->drawAt(position);
        }
        
        void LinearSpriteAnimator::updateFrame()
        {
            position = to;
        }
    }
}
