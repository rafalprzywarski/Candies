#pragma once
#include <GameCore/GameLogic.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace GameCore
    {
        struct MockGameLogic : GameLogic
        {
        public:
            MOCK_METHOD0(start, void());
            MOCK_METHOD2(swapItems, void(Location, Location));
        };
        
        typedef std::shared_ptr<MockGameLogic> MockGameLogicPtr;
    }
}
