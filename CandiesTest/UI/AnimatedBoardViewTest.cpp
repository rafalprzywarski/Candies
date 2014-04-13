#include <UI/AnimatedBoardView.hpp>
#include "MockSprite.hpp"
#include "MockGrid.hpp"
#include "MockSpriteAnimator.hpp"
#include <gtest/gtest.h>


using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct AnimatedBoardViewTest : Test
        {
            SpritePtr item3 = std::make_shared<StrictMock<MockSprite>>();
            SpritePtr item7 = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr selection = std::make_shared<StrictMock<MockSprite>>();
            const Logic::Location ANY_LOCATION{55, 12};
            const Logic::Location ITEM3_LOCATION{0, 0}, ITEM7_LOCATION{3, 2};
            const Position POSITION_WITH_NO_ITEM{34, 56};
            const Logic::Location LOCATION_WITH_NO_ITEM{5, 7};
            const Position ITEM3_POSITION{311, 322};
            const Position ITEM7_POSITION{711, 722};
            MockGridPtr grid = std::make_shared<StrictMock<MockGrid>>();
            MockSpriteAnimatorPtr animator = std::make_shared<NiceMock<MockSpriteAnimator>>();
            
            AnimatedBoardView board{{{3, item3}, {7, item7}}, selection, grid, animator};
            const Logic::ItemId INVALID_ID = 2;
            
            void expectGridConversions(Logic::Location loc, Position pos)
            {
                EXPECT_CALL(*grid, toPosition(loc)).WillRepeatedly(Return(pos));
                EXPECT_CALL(*grid, toLocation(pos)).WillRepeatedly(Return(loc));
                EXPECT_CALL(*grid, isValid(pos)).WillRepeatedly(Return(true));
            }
            
            AnimatedBoardViewTest()
            {
                EXPECT_CALL(*grid, isValid(_)).WillRepeatedly(Return(true));
                expectGridConversions(ITEM3_LOCATION, ITEM3_POSITION);
                expectGridConversions(ITEM7_LOCATION, ITEM7_POSITION);
                expectGridConversions(LOCATION_WITH_NO_ITEM, POSITION_WITH_NO_ITEM);
                ON_CALL(*animator, isAnimating()).WillByDefault(Return(false));
            }
        };

        TEST_F(AnimatedBoardViewTest, should_draw_nothing_when_created)
        {
            board.drawFrame();
        }
        
        TEST_F(AnimatedBoardViewTest, should_fail_when_added_item_has_invalid_id)
        {
            ASSERT_THROW(board.addItem(INVALID_ID, {0, 0}), std::out_of_range);
        }
        
        TEST_F(AnimatedBoardViewTest, should_not_select_anything_when_position_is_not_valid)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.addItem(7, ITEM7_LOCATION);

            Position POSITION{2, 3};
            EXPECT_CALL(*grid, isValid(POSITION)).WillRepeatedly(Return(false));

            board.selectItemAt(POSITION);

            ASSERT_TRUE(board.getSelectedItemLocations().empty());
        }

        TEST_F(AnimatedBoardViewTest, should_not_select_anything_when_there_are_no_items)
        {
            EXPECT_CALL(*grid, toLocation(_)).WillRepeatedly(Return(ANY_LOCATION));

            board.selectItemAt({2, 3});

            ASSERT_TRUE(board.getSelectedItemLocations().empty());
        }
        
        TEST_F(AnimatedBoardViewTest, should_select_nothing_when_created)
        {
            ASSERT_TRUE(board.getSelectedItemLocations().empty());
        }
        
        TEST_F(AnimatedBoardViewTest, should_select_items_at_given_coordinates_based_on_grid)
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
        
        TEST_F(AnimatedBoardViewTest, should_only_select_existing_items)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.addItem(7, ITEM7_LOCATION);
            
            board.selectItemAt(POSITION_WITH_NO_ITEM);
            ASSERT_TRUE(board.getSelectedItemLocations().empty());
        }
        
        TEST_F(AnimatedBoardViewTest, should_not_select_items_when_animator_is_animating)
        {
            EXPECT_CALL(*animator, isAnimating()).WillRepeatedly(Return(true));
            
            board.addItem(3, ITEM3_LOCATION);
            board.selectItemAt(ITEM3_POSITION);

            ASSERT_TRUE(board.getSelectedItemLocations().empty());
        }
        
        TEST_F(AnimatedBoardViewTest, should_clear_selection)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.addItem(7, ITEM7_LOCATION);

            board.selectItemAt(ITEM3_POSITION);
            board.selectItemAt(ITEM7_POSITION);
            board.clearSelection();
            
            ASSERT_TRUE(board.getSelectedItemLocations().empty());
        }

        TEST_F(AnimatedBoardViewTest, should_not_select_the_same_item_twice)
        {
            board.addItem(3, ITEM3_LOCATION);

            board.selectItemAt(ITEM3_POSITION);
            board.selectItemAt(ITEM3_POSITION);
            ASSERT_EQ(1u, board.getSelectedItemLocations().size());
        }
        
        TEST_F(AnimatedBoardViewTest, should_draw_items_then_the_selection)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.addItem(7, ITEM7_LOCATION);
            board.selectItemAt(ITEM3_POSITION);
            board.selectItemAt(ITEM7_POSITION);

            Expectation sprites = EXPECT_CALL(*animator, draw());
            EXPECT_CALL(*selection, drawAt(ITEM3_POSITION)).After(sprites);
            EXPECT_CALL(*selection, drawAt(ITEM7_POSITION)).After(sprites);
            
            board.drawFrame();
        }
        
        TEST_F(AnimatedBoardViewTest, should_swap_items)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.addItem(7, ITEM7_LOCATION);
            
            EXPECT_CALL(*animator, moveSprite(item3, ITEM3_POSITION, ITEM7_POSITION));
            EXPECT_CALL(*animator, moveSprite(item7, ITEM7_POSITION, ITEM3_POSITION));
            
            board.swapItems(ITEM3_LOCATION, ITEM7_LOCATION);
            
            EXPECT_CALL(*animator, moveSprite(item3, ITEM7_POSITION, ITEM3_POSITION));
            EXPECT_CALL(*animator, moveSprite(item7, ITEM3_POSITION, ITEM7_POSITION));

            board.swapItems(ITEM3_LOCATION, ITEM7_LOCATION);
        }
        
        TEST_F(AnimatedBoardViewTest, should_ignore_invalid_swaps)
        {
            board.addItem(3, ITEM3_LOCATION);
            
            EXPECT_CALL(*animator, moveSprite(_, _, _)).Times(0);

            board.swapItems(ITEM7_LOCATION, ITEM3_LOCATION);
            board.swapItems(ITEM3_LOCATION, ITEM7_LOCATION);
        }
        
        TEST_F(AnimatedBoardViewTest, should_remove_items)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.addItem(7, ITEM7_LOCATION);
            
            EXPECT_CALL(*animator, destroySpriteAt(item7, ITEM7_POSITION));
            
            board.removeItem(ITEM7_LOCATION);

            EXPECT_CALL(*animator, destroySpriteAt(_, _)).Times(0);
            board.removeItem(ITEM7_LOCATION);
        }
        
        TEST_F(AnimatedBoardViewTest, should_ignore_invalid_removals)
        {
            board.addItem(3, ITEM3_LOCATION);
            board.addItem(7, ITEM7_LOCATION);
            
            EXPECT_CALL(*animator, destroySpriteAt(_, _)).Times(0);
            board.removeItem(LOCATION_WITH_NO_ITEM);
        }
        
        TEST_F(AnimatedBoardViewTest, should_move_items)
        {
            board.addItem(3, ITEM3_LOCATION);
            
            EXPECT_CALL(*animator, moveSprite(item3, ITEM3_POSITION, ITEM7_POSITION));
            board.moveItem(ITEM3_LOCATION, ITEM7_LOCATION);
            
            EXPECT_CALL(*animator, destroySpriteAt(_, _));
            board.removeItem(ITEM7_LOCATION);
        }
        
        TEST_F(AnimatedBoardViewTest, should_ignore_invalid_moves)
        {
            board.addItem(3, ITEM3_LOCATION);
            
            EXPECT_CALL(*animator, moveSprite(_, _, _)).Times(0);
            board.moveItem(ITEM7_LOCATION, ITEM3_LOCATION);
        }
    }
}
