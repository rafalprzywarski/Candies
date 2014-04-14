#pragma once
#include "Animation.hpp"
#include "SpriteWithPosition.hpp"

namespace Candies
{
    namespace UI
    {
        class SmoothSwappingAnimation
        {
        public:
            SmoothSwappingAnimation(Position first, Position second, const SpritesWithPositions& sprites);
            SpritesWithPositions getFinalSprites() const;
        private:
            SpritesWithPositions finalSprites;
        };
    }
}
