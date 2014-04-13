#include "LinearSpriteAnimator.hpp"

namespace Candies
{
    namespace UI
    {
        void LinearSpriteAnimator::moveSprite(SpritePtr sprite, Position from, Position to)
        {
            this->sprite = sprite;
            this->from = from;
            this->position = from;
            this->to = to;
            startTime = timer->getTime();
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
            float elapsedTime = timer->getTime() - startTime;
            if (elapsedTime >= animationTime)
            {
                position = to;
                return;
            }
            position = lerp(from, to, elapsedTime / animationTime);
        }
        
        int LinearSpriteAnimator::lerp(int from, int to, float t)
        {
            return int(from + (to - from) * t);
        }

        Position LinearSpriteAnimator::lerp(Position from, Position to, float t)
        {
            return {lerp(from.x, to.x, t), lerp(from.y, to.y, t)};
        }

    }
}
