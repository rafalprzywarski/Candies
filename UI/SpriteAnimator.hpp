#pragma once
#include "Sprite.hpp"
#include <memory>

namespace Candies
{
    namespace UI
    {
        class SpriteAnimator
        {
        public:
            virtual ~SpriteAnimator() { }
            virtual void moveSprite(SpritePtr sprite, Position from, Position to) = 0;
            virtual void destroySpriteAt(Position at) = 0;
            virtual bool isAnimating() const = 0;
            virtual void draw() const = 0;
        };
        
        typedef std::shared_ptr<SpriteAnimator> SpriteAnimatorPtr;
    }
}
