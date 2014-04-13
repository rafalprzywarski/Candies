#pragma once
#include "ItemId.hpp"
#include "Location.hpp"
#include <memory>
#include <ostream>

namespace Candies
{
    namespace Logic
    {
        struct Movement
        {
            Location from, to;
            Movement(Location from, Location to) : from(from), to(to) { }
        };

        inline bool operator<(const Movement& left, const Movement& right)
        {
            return std::make_pair(left.from, left.to) < std::make_pair(right.from, right.to);
        }
        
        inline bool operator==(const Movement& left, const Movement& right)
        {
            return left.from == right.from && left.to == right.to;
        }
        
        inline std::ostream& operator<<(std::ostream& os, const Movement& m)
        {
            return os << "[" << m.from << " -> " << m.to << "]";
        }
        
        typedef std::vector<Movement> Movements;
        
        class GameObserver
        {
        public:
            virtual ~GameObserver() { }
            virtual void itemAdded(ItemId item, Location loc) = 0;
            virtual void itemsSwapped(Location loc1, Location loc2) = 0;
            virtual void itemsRemoved(const Locations& locs) = 0;
            virtual void itemsMoved(const Movements& movements) = 0;
        };
        
        typedef std::shared_ptr<GameObserver> GameObserverPtr;
    }
}
