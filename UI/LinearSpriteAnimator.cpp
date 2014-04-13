#include "LinearSpriteAnimator.hpp"

namespace Candies
{
    namespace UI
    {
        void LinearSpriteAnimator::moveSprite(SpritePtr sprite, Position from, Position to)
        {
            sprites.emplace_back(sprite, from, to);
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
            for (auto& sprite : sprites)
                sprite.draw();
        }
        
        void LinearSpriteAnimator::updateFrame()
        {
            float elapsedTime = timer->getTime() - startTime;
            for (auto& sprite : sprites)
                sprite.update(elapsedTime / animationTime);
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
        
        void LinearSpriteAnimator::SpriteState::update(float completionFactor)
        {
            if (completionFactor >= 1)
            {
                position = to;
                return;
            }
            position = lerp(from, to, completionFactor);
        }

    }
}
