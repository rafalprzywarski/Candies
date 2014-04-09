#pragma once
#include <UI/BoardView.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockBoardView : BoardView
        {
            MOCK_METHOD1(selectItemAt, void(Position pos));
            MOCK_CONST_METHOD0(getSelectedItemLocations, Logic::Locations());
            MOCK_METHOD0(clearSelection, void());
        };
        
        typedef std::shared_ptr<MockBoardView> MockBoardViewPtr;
    }
}
