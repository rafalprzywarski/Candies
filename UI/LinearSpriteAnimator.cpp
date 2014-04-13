#include "LinearSpriteAnimator.hpp"
#include <algorithm>
#include <cmath>

namespace Candies
{
    namespace UI
    {
        void LinearSpriteAnimator::moveSprite(SpritePtr sprite, Position from, Position to)
        {
            if (!chainSprite(sprite, from, to))
                addNewSprite(sprite, from, to, timer->getTime());
        }
        
        void LinearSpriteAnimator::swapSprites(SpritePtr sprite1, Position from1, SpritePtr sprite2, Position from2)
        {
            float currentTime = timer->getTime();
            auto spriteFrom1 = findSpriteForChaining(from1);
            auto spriteFrom2 = findSpriteForChaining(from2);
            
            chainOrAddNewSprite(spriteFrom1, sprite1, from1, from2, currentTime);
            chainOrAddNewSprite(spriteFrom2, sprite2, from2, from1, currentTime);
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
        
        LinearSpriteAnimator::Sprites::iterator LinearSpriteAnimator::findSpriteForChaining(Position from)
        {
            return std::find_if(sprites.begin(), sprites.end(), [=](const AnimatedSprite& s) { return s.shouldChainWith(from); });
        }
        
        void LinearSpriteAnimator::chainOrAddNewSprite(Sprites::iterator at, SpritePtr sprite, Position from, Position to, float currentTime)
        {
            if (at == sprites.end())
                addNewSprite(sprite, from, to, currentTime);
            else
                at->addTransition(to);
        }
        
        bool LinearSpriteAnimator::chainSprite(SpritePtr sprite, Position from, Position to)
        {
            auto it = findSpriteForChaining(from);
            if (it == sprites.end())
                return false;
            it->addTransition(to);
            return true;
        }
        
        void LinearSpriteAnimator::addNewSprite(SpritePtr sprite, Position from, Position to, float currentTime)
        {
            sprites.emplace_back(sprite, from, currentTime, animationVelocity);
            sprites.back().addTransition(to);
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

        bool LinearSpriteAnimator::AnimatedSprite::shouldChainWith(Position from) const
        {
            return (!destinations.empty() && destinations.back() == from) || position == from;
        }

        void LinearSpriteAnimator::AnimatedSprite::addTransition(Position to)
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
