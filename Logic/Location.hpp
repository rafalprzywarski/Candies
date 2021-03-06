#pragma once
#include <ostream>
#include <vector>
#include <functional>

namespace Candies
{
    namespace Logic
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
        
        inline bool operator<(const Location& left, const Location& right)
        {
            return std::make_pair(left.x, left.y) < std::make_pair(right.x, right.y);
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
    struct hash<Candies::Logic::Location>
    {
        std::size_t operator()(const Candies::Logic::Location& loc) const
        {
            std::hash<unsigned> h;
            return h(loc.x) ^ h(loc.y);
        }
    };
}
