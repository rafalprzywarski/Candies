#include "LinearSpriteAnimator.hpp"
#include <algorithm>

namespace Candies
{
    namespace UI
    {
        void LinearSpriteAnimator::moveSprite(SpritePtr sprite, Position from, Position to)
        {
            for (auto& s : sprites)
                if (s.shouldChainWith(from))
                {
                    s.chain(to);
                    return;
                }
            sprites.emplace_back(sprite, from, to, timer->getTime() / animationTime);
        }
        
        void LinearSpriteAnimator::destroySpriteAt(SpritePtr sprite, Position at)
        {
            for (auto& s : sprites)
                if (s.shouldChainWith(at))
                {
                    s.markForDestruction();
                    return;
                }
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
            sprites.erase(std::remove_if(sprites.begin(), sprites.end(), [](const AnimatedSprite& s) { return s.isDestroyed(); }), sprites.end());
        }
        
        int LinearSpriteAnimator::lerp(int from, int to, float t)
        {
            return int(from + (to - from) * t);
        }

        Position LinearSpriteAnimator::lerp(Position from, Position to, float t)
        {
            return {lerp(from.x, to.x, t), lerp(from.y, to.y, t)};
        }

        void LinearSpriteAnimator::AnimatedSprite::draw() const
        {
            sprite->drawAt(position);
        }
        
        void LinearSpriteAnimator::AnimatedSprite::update(float currentTime)
        {
            float completionFactor = currentTime - startTime;
            while (completionFactor >= 1 && !destinations.empty())
            {
                position = from = destinations.at(0);
                from = destinations.at(0);
                destinations.erase(destinations.begin());
                completionFactor -= 1;
            }
            if (!destinations.empty())
                position = lerp(from, destinations.at(0), completionFactor);
        }

        bool LinearSpriteAnimator::AnimatedSprite::isDestroyed() const
        {
            return destinations.empty() && shouldBeDestroyed;
        }

    }
}
