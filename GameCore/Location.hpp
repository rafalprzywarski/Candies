#pragma once
#include <ostream>
#include <vector>
#include <functional>

namespace Candies
{
    namespace GameCore
    {
        struct Location
        {
            unsigned x, y;
            Location(unsigned x, unsigned y) : x(x), y(y) { }
        };
        
        typedef std::vector<Location> Locations;

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

namespace std
{
    template <>
    struct hash<Candies::GameCore::Location>
    {
        std::size_t operator()(const Candies::GameCore::Location& loc) const
        {
            std::hash<unsigned> h;
            return h(loc.x) ^ h(loc.y);
        }
    };
}
