#include <GameUI/MouseItemSelector.hpp>
#include "MockBoardView.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct MouseItemSelectorTest : Test
        {
            MockBoardViewPtr view = std::make_shared<MockBoardView>();
            MouseItemSelector selector{view};
            const Position POS{11, 12};
            const GameCore::Locations NO_SELECTION;
        };
        
        TEST_F(MouseItemSelectorTest, should_try_to_select_an_item_from_board_view)
        {
            InSequence order;
            EXPECT_CALL(*view, selectItemAt(POS));
            EXPECT_CALL(*view, getSelectedItemLocations()).WillRepeatedly(Return(NO_SELECTION));
            selector.mouseDown(POS.x, POS.y);
        }
        
    }
}
