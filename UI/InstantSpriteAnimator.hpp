#pragma once
#include "SpriteAnimator.hpp"
#include <memory>

namespace Candies
{
    namespace UI
    {
        class InstantSpriteAnimator : public SpriteAnimator
        {
        public:
            void moveSprite(SpritePtr sprite, Position from, Position to)
            {
                sprites.erase(SpriteWithPosition{sprite, from});
                sprites.insert({sprite, to});
            }
            
            void destroySpriteAt(SpritePtr sprite, Position at)
            {
                sprites.erase({sprite, at});
            }
            void draw() const
            {
                for (auto const& s : sprites)
                    s.sprite->drawAt(s.position);
            }
        private:
            
            struct SpriteWithPosition
            {
                SpritePtr sprite;
                Position position;
                
                bool operator==(const SpriteWithPosition& right) const
                {
                    return sprite == right.sprite && position == right.position;
                }
            };
            
            struct SpriteWithPositionHash
            {
                std::size_t operator()(const SpriteWithPosition& s) const
                {
                    return std::hash<SpritePtr>()(s.sprite) ^ std::hash<Position>()(s.position);
                }
            };
            
            std::unordered_set<SpriteWithPosition, SpriteWithPositionHash> sprites;
        };
    }
}
