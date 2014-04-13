#pragma once
#include "SpriteAnimator.hpp"
#include <memory>

namespace Candies
{
    namespace UI
    {
        class LinearSpriteAnimator : public SpriteAnimator
        {
        public:
            void moveSprite(SpritePtr sprite, Position from, Position to);
            void destroySpriteAt(SpritePtr sprite, Position at);
            bool isAnimating() const;
            void draw() const;
        private:
            SpritePtr sprite;
            Position from{0, 0};
        };
    }
}
