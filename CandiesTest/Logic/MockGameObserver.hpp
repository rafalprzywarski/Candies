#pragma once
#include <Logic/GameObserver.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace Logic
    {
        struct MockGameObserver : GameObserver
        {
            MOCK_METHOD2(itemAdded, void(ItemId item, Location loc));
            MOCK_METHOD2(itemsSwapped, void(Location loc1, Location loc2));
            MOCK_METHOD1(itemsRemoved, void(const Locations& locs));
            MOCK_METHOD1(itemsMoved, void(const Movements& movements));
        };
        
        typedef std::shared_ptr<MockGameObserver> MockGameObserverPtr;
    }
}
