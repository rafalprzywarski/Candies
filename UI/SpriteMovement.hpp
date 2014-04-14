#pragma once
#include "Position.hpp"
#include <ostream>
#include <vector>

namespace Candies
{
    namespace UI
    {
        struct SpriteMovement
        {
            Position from, to;
            SpriteMovement(Position from, Position to) : from(from), to(to) { }
        };
        
        inline bool operator==(const SpriteMovement& left, const SpriteMovement& right)
        {
            return left.from == right.from && left.to == right.to;
        }
        
        inline std::ostream& operator<<(std::ostream& os, const SpriteMovement& m)
        {
            return os << "[" << m.from << " -> " << m.to << "]";
        }
        
        typedef std::vector<SpriteMovement> SpriteMovements;
    }
}
