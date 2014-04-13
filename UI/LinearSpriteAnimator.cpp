#include "LinearSpriteAnimator.hpp"

namespace Candies
{
    namespace UI
    {
        void LinearSpriteAnimator::moveSprite(SpritePtr sprite, Position from, Position to)
        {
            sprites.emplace_back(sprite, from, to, timer->getTime() / animationTime);
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
            for (auto& sprite : sprites)
                sprite.draw();
        }
        
        void LinearSpriteAnimator::updateFrame()
        {
            float currentTime = timer->getTime() / animationTime;
            for (auto& sprite : sprites)
                sprite.update(currentTime);
        }
        
        int LinearSpriteAnimator::lerp(int from, int to, float t)
        {
            return int(from + (to - from) * t);
        }

        Position LinearSpriteAnimator::lerp(Position from, Position to, float t)
        {
            return {lerp(from.x, to.x, t), lerp(from.y, to.y, t)};
        }

        void LinearSpriteAnimator::SpriteState::draw() const
        {
            sprite->drawAt(position);
        }
        
        void LinearSpriteAnimator::SpriteState::update(float currentTime)
        {
            float completionFactor = currentTime - startTime;
            if (completionFactor >= 1)
            {
                position = to;
                return;
            }
            position = lerp(from, to, completionFactor);
        }

    }
}
