#include <UI/StaticBoardView.hpp>
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
            MockSpritePtr selection = std::make_shared<StrictMock<MockSprite>>();
            const int GRID_SIZE = 9;
            const Position POSITION = { 23, -17 };
            const Logic::Location ITEM3_LOCATION{0, 0}, ITEM7_LOCATION{3, 2};
            const Position ITEM3_POSITION{POSITION.x, POSITION.y};
            const Position ITEM7_POSITION{POSITION.x + GRID_SIZE * 3, POSITION.y + GRID_SIZE * 2};
            StaticBoardView board{{{3, item3}, {7, item7}}, selection, GRID_SIZE, POSITION};
            const Logic::ItemId INVALID_ID = 2;
        };

        TEST_F(StaticBoardViewTest, should_display_nothing_when_created)
        {
            board.update();
        }
        
        TEST_F(StaticBoardViewTest, should_display_added_items_according_to_board_position_and_grid_size)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.addItem(7, ITEM7_LOCATION);
            EXPECT_CALL(*item3, drawAt(ITEM3_POSITION));
            EXPECT_CALL(*item7, drawAt(ITEM7_POSITION));
            
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
        
        TEST_F(StaticBoardViewTest, should_select_items_at_given_coordinates)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.addItem(7, ITEM7_LOCATION);

            board.selectItemAt(POSITION);
            ASSERT_EQ(1u, board.getSelectedItemLocations().size());
            ASSERT_EQ(ITEM3_LOCATION, board.getSelectedItemLocations().back());
            
            board.selectItemAt({POSITION.x + GRID_SIZE * 3, POSITION.y + GRID_SIZE * 2});
            ASSERT_EQ(2u, board.getSelectedItemLocations().size());
            ASSERT_EQ(ITEM7_LOCATION, board.getSelectedItemLocations().at(1));

            board.clearSelection();
            board.selectItemAt({POSITION.x + GRID_SIZE - 1, POSITION.y});
            ASSERT_EQ(ITEM3_LOCATION, board.getSelectedItemLocations().at(0));

            board.clearSelection();
            board.selectItemAt({POSITION.x, POSITION.y + GRID_SIZE - 1});
            ASSERT_EQ(ITEM3_LOCATION, board.getSelectedItemLocations().at(0));

        }
        
        TEST_F(StaticBoardViewTest, should_not_select_items_not_touching_given_coordinates)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.addItem(7, ITEM7_LOCATION);
            
            board.selectItemAt({POSITION.x - 1, POSITION.y});
            ASSERT_TRUE(board.getSelectedItemLocations().empty());

            board.selectItemAt({POSITION.x, POSITION.y - 1});
            ASSERT_TRUE(board.getSelectedItemLocations().empty());
            
            board.selectItemAt({POSITION.x + GRID_SIZE * 2, POSITION.y + GRID_SIZE});
            ASSERT_TRUE(board.getSelectedItemLocations().empty());
        }
        
        TEST_F(StaticBoardViewTest, should_clear_selection)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.addItem(7, ITEM7_LOCATION);

            board.selectItemAt(ITEM3_POSITION);
            board.selectItemAt(ITEM7_POSITION);
            board.clearSelection();
            
            ASSERT_TRUE(board.getSelectedItemLocations().empty());
        }

        TEST_F(StaticBoardViewTest, should_not_select_the_same_item_twice)
        {
            board.addItem(3, ITEM3_LOCATION);

            board.selectItemAt(ITEM3_POSITION);
            board.selectItemAt(ITEM3_POSITION);
            ASSERT_EQ(1u, board.getSelectedItemLocations().size());
        }
        
        TEST_F(StaticBoardViewTest, should_display_item_selection)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.addItem(7, ITEM7_LOCATION);
            board.selectItemAt(ITEM3_POSITION);
            board.selectItemAt(ITEM7_POSITION);

            Sequence item3WithMarker, item7WithMarker;
            EXPECT_CALL(*item3, drawAt(_)).InSequence(item3WithMarker);
            EXPECT_CALL(*selection, drawAt(ITEM3_POSITION)).InSequence(item3WithMarker);
            EXPECT_CALL(*item7, drawAt(_)).InSequence(item7WithMarker);
            EXPECT_CALL(*selection, drawAt(ITEM7_POSITION)).InSequence(item7WithMarker);
            
            board.update();
        }
        
        TEST_F(StaticBoardViewTest, should_swap_items)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.addItem(7, ITEM7_LOCATION);
            
            board.swapItems(ITEM3_LOCATION, ITEM7_LOCATION);
            
            EXPECT_CALL(*item3, drawAt(ITEM7_POSITION));
            EXPECT_CALL(*item7, drawAt(ITEM3_POSITION));
            
            board.update();
        }
    }
}
