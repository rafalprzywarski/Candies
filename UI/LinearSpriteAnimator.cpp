#include "LinearSpriteAnimator.hpp"
#include <algorithm>
#include <cmath>

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
            sprites.emplace_back(sprite, from, to, timer->getTime(), animationVelocity);
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
            float currentTime = timer->getTime();
            for (auto& sprite : sprites)
                sprite.update(currentTime);
            sprites.erase(std::remove_if(sprites.begin(), sprites.end(), [](const AnimatedSprite& s) { return s.isDestroyed(); }), sprites.end());
        }
        
        int LinearSpriteAnimator::lerp(int from, int to, float t)
        {
            return int(std::round(from + (to - from) * t));
        }

        float LinearSpriteAnimator::distance(Position from, Position to)
        {
            float dx = from.x - to.x, dy = from.y - to.y;
            return std::sqrt(dx * dx + dy * dy);
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
            float currentDistance = getCurrentDistance(currentTime);
            float currentTransitionLength = distance(from, destinations.front());
            while (!destinations.empty() && currentDistance >= currentTransitionLength)
            {
                finishCurrentTransition(currentTransitionLength);
                currentDistance = getCurrentDistance(currentTime);
            }
            if (!destinations.empty())
                position = lerp(from, destinations.at(0), currentDistance / distance(from, destinations.front()));
        }

        bool LinearSpriteAnimator::AnimatedSprite::isDestroyed() const
        {
            return destinations.empty() && shouldBeDestroyed;
        }

        bool LinearSpriteAnimator::AnimatedSprite::shouldChainWith(Position from)
        {
            return (!destinations.empty() && destinations.back() == from) || position == from;
        }

        void LinearSpriteAnimator::AnimatedSprite::chain(Position to)
        {
            destinations.push_back(to);
        }
        
        void LinearSpriteAnimator::AnimatedSprite::markForDestruction()
        {
            shouldBeDestroyed = true;
        }

        void LinearSpriteAnimator::AnimatedSprite::finishCurrentTransition(float currentTransitionLength)
        {
            position = from = destinations.at(0);
            from = destinations.at(0);
            destinations.erase(destinations.begin());
            fromTime += currentTransitionLength / velocity;
        }
                                                       
        float LinearSpriteAnimator::AnimatedSprite::getCurrentDistance(float currentTime) const
        {
            return (currentTime - fromTime) * velocity;
        }

    }
}
