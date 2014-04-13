#pragma once
#include <UI/Grid.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockGrid : Grid
        {
            MOCK_CONST_METHOD1(toPosition, Position(Logic::Location loc));
            MOCK_CONST_METHOD1(isValid, bool(Position pos));
            MOCK_CONST_METHOD1(toLocation, Logic::Location(Position pos));
        };
        
        typedef std::shared_ptr<MockGrid> MockGridPtr;
    }
}
