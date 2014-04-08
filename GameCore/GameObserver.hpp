#pragma once
#include "ItemId.hpp"
#include "Location.hpp"
#include <memory>

namespace Candies
{
    namespace GameCore
    {
        class GameObserver
        {
        public:
            virtual ~GameObserver() { }
            virtual void itemAdded(ItemId item, Location loc) = 0;
        };
        
        typedef std::shared_ptr<GameObserver> GameObserverPtr;
    }
}
