#include <GameUI/MouseItemSelector.hpp>
#include "MockBoardView.hpp"
#include "MockGameLogic.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct MouseItemSelectorTest : Test
        {
            MockBoardViewPtr view = std::make_shared<StrictMock<MockBoardView>>();
            GameCore::MockGameLogicPtr logic = std::make_shared<StrictMock<GameCore::MockGameLogic>>();
            MouseItemSelector selector{view, logic};
            const Position POS{11, 12};
            const GameCore::Locations NO_SELECTION, TWO_ITEMS{{4, 3}, {1, 2}};
        };
        
        TEST_F(MouseItemSelectorTest, should_try_to_select_an_item_from_board_view)
        {
            InSequence order;
            EXPECT_CALL(*view, selectItemAt(POS));
            EXPECT_CALL(*view, getSelectedItemLocations()).WillRepeatedly(Return(NO_SELECTION));
            selector.mouseDown(POS.x, POS.y);
        }
        
        TEST_F(MouseItemSelectorTest, should_try_to_swap_items_when_second_item_is_selected_and_clear_selection)
        {
            EXPECT_CALL(*view, selectItemAt(_));
            EXPECT_CALL(*view, getSelectedItemLocations()).WillRepeatedly(Return(TWO_ITEMS));
            EXPECT_CALL(*logic, swapItems(TWO_ITEMS[0], TWO_ITEMS[1]));
            EXPECT_CALL(*view, clearSelection());
            selector.mouseDown(0, 0);
        }
        
    }
}
