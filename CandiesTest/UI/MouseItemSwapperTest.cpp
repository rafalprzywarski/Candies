#include <UI/MouseItemSwapper.hpp>
#include "MockBoardView.hpp"
#include "MockGameLogic.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct MouseItemSwapperTest : Test
        {
            MockBoardViewPtr view = std::make_shared<StrictMock<MockBoardView>>();
            Logic::MockGameLogicPtr logic = std::make_shared<StrictMock<Logic::MockGameLogic>>();
            MouseItemSwapper selector{view, logic};
            const Position DOWN_POS{11, 12}, UP_POS{13, 14};
            const Logic::Locations NO_SELECTION, ONE_ITEM{{5, 6}}, TWO_ITEMS{{4, 3}, {1, 2}};
        };
        
        TEST_F(MouseItemSwapperTest, should_try_to_select_an_item_from_board_view_on_mouse_up)
        {
            selector.mouseDown(DOWN_POS);
            InSequence order;
            EXPECT_CALL(*view, selectItemAt(DOWN_POS));
            EXPECT_CALL(*view, getSelectedItemLocations()).WillRepeatedly(Return(NO_SELECTION));
            EXPECT_CALL(*view, selectItemAt(UP_POS));
            EXPECT_CALL(*view, getSelectedItemLocations()).WillRepeatedly(Return(NO_SELECTION));
            selector.mouseUp(UP_POS);
        }
        
        TEST_F(MouseItemSwapperTest, should_try_to_swap_items_when_second_item_is_selected_with_mouse_up_and_clear_selection)
        {
            selector.mouseDown(DOWN_POS);
            InSequence order;
            EXPECT_CALL(*view, selectItemAt(DOWN_POS));
            EXPECT_CALL(*view, getSelectedItemLocations()).WillRepeatedly(Return(ONE_ITEM));
            EXPECT_CALL(*view, selectItemAt(UP_POS));
            EXPECT_CALL(*view, getSelectedItemLocations()).WillRepeatedly(Return(TWO_ITEMS));
            EXPECT_CALL(*logic, swapItems(TWO_ITEMS[0], TWO_ITEMS[1]));
            EXPECT_CALL(*view, clearSelection());
            selector.mouseUp(UP_POS);
        }
        
        TEST_F(MouseItemSwapperTest, should_try_to_swap_items_when_second_item_is_selected_with_mouse_down_and_clear_selection)
        {
            selector.mouseDown(DOWN_POS);
            InSequence order;
            EXPECT_CALL(*view, selectItemAt(DOWN_POS));
            EXPECT_CALL(*view, getSelectedItemLocations()).WillRepeatedly(Return(TWO_ITEMS));
            EXPECT_CALL(*logic, swapItems(_, _));
            EXPECT_CALL(*view, clearSelection());
            selector.mouseUp(UP_POS);
        }
        
        TEST_F(MouseItemSwapperTest, should_do_nothing_when_disabled)
        {
            selector.disable();
            selector.mouseDown(DOWN_POS);
            selector.mouseUp(UP_POS);
        }
        
    }
}
