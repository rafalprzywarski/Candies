#include <GameUI/StaticBoardView.hpp>
#include "MockSprite.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct StaticBoardViewTest : Test
        {
            MockSpritePtr item3 = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr item7 = std::make_shared<StrictMock<MockSprite>>();
            const int GRID_SIZE = 9;
            const Position POSITION = { 23, -17 };
            StaticBoardView board{{{3, item3}, {7, item7}}, GRID_SIZE, POSITION};
            const GameCore::ItemId INVALID_ID = 2;
        };

        TEST_F(StaticBoardViewTest, should_display_nothing_when_created)
        {
            board.update();
        }
        
        TEST_F(StaticBoardViewTest, should_display_added_items_according_to_board_position_and_grid_size)
        {
            board.addItem(3, {0, 0});
            board.addItem(7, {3, 2});
            EXPECT_CALL(*item3, drawAt(Position(POSITION.x, POSITION.y)));
            EXPECT_CALL(*item7, drawAt(Position(POSITION.x + 3 * GRID_SIZE, POSITION.y + 2 * GRID_SIZE)));
            
            board.update();
        }
        
        TEST_F(StaticBoardViewTest, should_fail_when_added_item_has_invalid_id)
        {
            ASSERT_THROW(board.addItem(INVALID_ID, {0, 0}), std::out_of_range);
        }
        
        TEST_F(StaticBoardViewTest, should_not_select_anything_when_there_are_no_items)
        {
            board.selectItemAt({2, 3});
            ASSERT_TRUE(board.getSelectedItemLocations().empty());
        }
        
        TEST_F(StaticBoardViewTest, should_select_nothing_when_created)
        {
            ASSERT_TRUE(board.getSelectedItemLocations().empty());
        }
    }
}
