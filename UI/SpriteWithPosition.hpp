#pragma once
#include "Sprite.hpp"
#include "Position.hpp"
#include <vector>

namespace Candies
{
    namespace UI
    {
        struct SpriteWithPosition
        {
            SpritePtr sprite;
            Position position;
            SpriteWithPosition(SpritePtr sprite, Position position)
            : sprite(std::move(sprite)), position(position) { }
        };
        
        inline bool operator==(const SpriteWithPosition& left, const SpriteWithPosition& right)
        {
            return left.sprite == right.sprite && left.position == right.position;
        }
        
        typedef std::vector<SpriteWithPosition> SpritesWithPositions;
    }
}
