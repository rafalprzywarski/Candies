#pragma once
#include <ostream>

namespace Candies
{
    namespace GameCore
    {
        struct Location
        {
            unsigned x, y;
            Location(unsigned x, unsigned y) : x(x), y(y) { }
        };

        inline bool operator==(const Location& left, const Location& right)
        {
            return left.x == right.x && left.y == right.y;
        }
        
        inline std::ostream& operator<<(std::ostream& os, const Location& p)
        {
            return os << "[" << p.x << " " << p.y << "]";
        }
    }
}
