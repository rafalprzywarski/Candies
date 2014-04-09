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
        };
        
        typedef std::shared_ptr<MockGameObserver> MockGameObserverPtr;
    }
}
