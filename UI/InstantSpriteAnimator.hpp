#pragma once
#include "SpriteAnimator.hpp"
#include <unordered_map>
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
                sprites.erase(from);
                sprites.insert({to, sprite});
            }
            
            void destroySpriteAt(Position at)
            {
                sprites.erase(at);
            }
            
            bool isAnimating() const
            {
                return false;
            }
            
            void draw() const
            {
                for (auto const& s : sprites)
                    s.second->drawAt(s.first);
            }
        private:
            
            struct SpriteWithPosition
            {
                SpritePtr sprite;
                Position position;
                
                bool operator==(const SpriteWithPosition& right) const
                {
                    return position == right.position;
                }
            };
            
            struct SpriteWithPositionHash
            {
                std::size_t operator()(const SpriteWithPosition& s) const
                {
                    return std::hash<Position>()(s.position);
                }
            };
            
            std::unordered_map<Position, SpritePtr> sprites;
        };
    }
}
