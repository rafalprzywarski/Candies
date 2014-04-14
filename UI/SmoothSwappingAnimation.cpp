#include "SmoothSwappingAnimation.hpp"

namespace Candies
{
    namespace UI
    {
        SmoothSwappingAnimation::SmoothSwappingAnimation(Position first, Position second, const SpritesWithPositions& sprites)
        : finalSprites(sprites)
        {
            for (auto& s : finalSprites)
                if (s.position == first)
                    s.position = second;
                else if (s.position == second)
                    s.position = first;
        }
        
        SpritesWithPositions SmoothSwappingAnimation::getFinalSprites() const
        {
            return finalSprites;
        }
    }
}
