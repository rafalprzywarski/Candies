#include <UI/StaticBoardView.hpp>
#include "MockSprite.hpp"
#include "MockGrid.hpp"
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
            const Logic::Location ANY_LOCATION{55, 12};
            const Logic::Location ITEM3_LOCATION{0, 0}, ITEM7_LOCATION{3, 2};
            const Position POSITION_WITH_NO_ITEM{34, 56};
            const Logic::Location LOCATION_WITH_NO_ITEM{5, 7};
            const Position ITEM3_POSITION{311, 322};
            const Position ITEM7_POSITION{711, 722};
            MockGridPtr grid = std::make_shared<StrictMock<MockGrid>>();
            
            StaticBoardView board{{{3, item3}, {7, item7}}, selection, grid};
            const Logic::ItemId INVALID_ID = 2;
            
            void expectGridConversions(Logic::Location loc, Position pos)
            {
                EXPECT_CALL(*grid, toPosition(loc)).WillRepeatedly(Return(pos));
                EXPECT_CALL(*grid, toLocation(pos)).WillRepeatedly(Return(loc));
                EXPECT_CALL(*grid, isValid(pos)).WillRepeatedly(Return(true));
            }
            
            StaticBoardViewTest()
            {
                EXPECT_CALL(*grid, isValid(_)).WillRepeatedly(Return(true));
                expectGridConversions(ITEM3_LOCATION, ITEM3_POSITION);
                expectGridConversions(ITEM7_LOCATION, ITEM7_POSITION);
                expectGridConversions(LOCATION_WITH_NO_ITEM, POSITION_WITH_NO_ITEM);
            }
        };

        TEST_F(StaticBoardViewTest, should_display_nothing_when_created)
        {
            board.update();
        }
        
        TEST_F(StaticBoardViewTest, should_display_added_items_according_to_grid_position)
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
        
        TEST_F(StaticBoardViewTest, should_not_select_anything_when_position_is_not_valid)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.addItem(7, ITEM7_LOCATION);

            Position POSITION{2, 3};
            EXPECT_CALL(*grid, isValid(POSITION)).WillRepeatedly(Return(false));

            board.selectItemAt(POSITION);

            ASSERT_TRUE(board.getSelectedItemLocations().empty());
        }

        TEST_F(StaticBoardViewTest, should_not_select_anything_when_there_are_no_items)
        {
            EXPECT_CALL(*grid, toLocation(_)).WillRepeatedly(Return(ANY_LOCATION));

            board.selectItemAt({2, 3});

            ASSERT_TRUE(board.getSelectedItemLocations().empty());
        }
        
        TEST_F(StaticBoardViewTest, should_select_nothing_when_created)
        {
            ASSERT_TRUE(board.getSelectedItemLocations().empty());
        }
        
        TEST_F(StaticBoardViewTest, should_select_items_at_given_coordinates_based_on_grid)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.addItem(7, ITEM7_LOCATION);

            Position POSITION{88, 99};
            EXPECT_CALL(*grid, toLocation(POSITION)).WillRepeatedly(Return(ITEM3_LOCATION));
            
            board.selectItemAt(POSITION);
            
            ASSERT_EQ(1u, board.getSelectedItemLocations().size());
            ASSERT_EQ(ITEM3_LOCATION, board.getSelectedItemLocations().back());

            EXPECT_CALL(*grid, toLocation(_)).WillRepeatedly(Return(ITEM7_LOCATION));
            board.selectItemAt({100, 200});
            
            ASSERT_EQ(2u, board.getSelectedItemLocations().size());
            ASSERT_EQ(ITEM7_LOCATION, board.getSelectedItemLocations().at(1));
        }
        
        TEST_F(StaticBoardViewTest, should_only_select_existing_items)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.addItem(7, ITEM7_LOCATION);
            
            board.selectItemAt(POSITION_WITH_NO_ITEM);
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
        
        TEST_F(StaticBoardViewTest, should_ignore_invalid_swaps)
        {
            board.addItem(3, ITEM3_LOCATION);
            
            board.swapItems(ITEM7_LOCATION, ITEM3_LOCATION);

            EXPECT_CALL(*item3, drawAt(ITEM3_POSITION));
            board.update();
            
            board.swapItems(ITEM3_LOCATION, ITEM7_LOCATION);

            EXPECT_CALL(*item3, drawAt(ITEM3_POSITION));
            board.update();
        }
        
        TEST_F(StaticBoardViewTest, should_remove_items)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.addItem(7, ITEM7_LOCATION);
            board.removeItem(ITEM7_LOCATION);
            
            EXPECT_CALL(*item3, drawAt(ITEM3_POSITION));
            board.update();
        }
        
        TEST_F(StaticBoardViewTest, should_ignore_invalid_removals)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.removeItem(ITEM7_LOCATION);
            
            EXPECT_CALL(*item3, drawAt(ITEM3_POSITION));
            board.update();
        }
        
        TEST_F(StaticBoardViewTest, should_move_items)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.moveItem(ITEM3_LOCATION, ITEM7_LOCATION);
            
            EXPECT_CALL(*item3, drawAt(ITEM7_POSITION));
            board.update();
        }
        
        TEST_F(StaticBoardViewTest, should_ignore_invalid_moves)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.moveItem(ITEM7_LOCATION, ITEM3_LOCATION);

            EXPECT_CALL(*item3, drawAt(ITEM3_POSITION));
            board.update();
        }
    }
}
