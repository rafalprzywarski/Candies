#pragma once
#include "ItemId.hpp"
#include "Location.hpp"
#include <memory>

namespace Candies
{
    namespace Logic
    {
        class GameObserver
        {
        public:
            virtual ~GameObserver() { }
            virtual void itemAdded(ItemId item, Location loc) = 0;
            virtual void itemsSwapped(Location loc1, Location loc2) = 0;
            virtual void itemRemoved(Location loc) = 0;
        };
        
        typedef std::shared_ptr<GameObserver> GameObserverPtr;
    }
}
