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
        };
        
        typedef std::shared_ptr<MockGameLogic> MockGameLogicPtr;
    }
}
