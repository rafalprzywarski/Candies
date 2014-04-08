#pragma once
#include <ostream>

namespace Candies
{
    namespace UI
    {
        struct Position
        {
            int x, y;
            Position(int x, int y) : x(x), y(y) { }
        };
        
        inline bool operator==(const Position& left, const Position& right)
        {
            return left.x == right.x && left.y == right.y;
        }
        
        inline std::ostream& operator<<(std::ostream& os, const Position& p)
        {
            return os << "[" << p.x << " " << p.y << "]";
        }
    }
}
