#include <UI/AnimatedBoardView2.hpp>
#include "MockSprite.hpp"
#include "MockGrid.hpp"
#include "MockBoardAnimator.hpp"
#include <gtest/gtest.h>


using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct AnimatedBoardView2Test : Test
        {
            SpritePtr item3 = std::make_shared<StrictMock<MockSprite>>();
            SpritePtr item7 = std::make_shared<StrictMock<MockSprite>>();
            SpritePtr item9 = std::make_shared<StrictMock<MockSprite>>();
            SpritePtr item13 = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr selection = std::make_shared<StrictMock<MockSprite>>();
            const Logic::Location ITEM3_LOCATION{0, 0}, ITEM7_LOCATION{3, 2};
            const Logic::Location ITEM9_LOCATION{6, 7}, ITEM13_LOCATION{8, 10};
            const Position ITEM3_POSITION{311, 322};
            const Position ITEM7_POSITION{711, 722};
            const Position ITEM9_POSITION{911, 922};
            const Position ITEM13_POSITION{1311, 1322};
            MockGridPtr grid = std::make_shared<NiceMock<MockGrid>>();
            MockBoardAnimatorPtr animator = std::make_shared<NiceMock<MockBoardAnimator>>();
            
            AnimatedBoardView2 board{{{3, item3}, {7, item7}, {9, item9}, {13, item13}}, selection, grid, animator};
            const Logic::ItemId INVALID_ID = 2;
            
            void defaultGridConversion(Logic::Location loc, Position pos)
            {
                ON_CALL(*grid, toPosition(loc)).WillByDefault(Return(pos));
                ON_CALL(*grid, toLocation(pos)).WillByDefault(Return(loc));
                ON_CALL(*grid, isValid(pos)).WillByDefault(Return(true));
            }
            
            AnimatedBoardView2Test()
            {
                ON_CALL(*grid, isValid(_)).WillByDefault(Return(true));
                defaultGridConversion(ITEM3_LOCATION, ITEM3_POSITION);
                defaultGridConversion(ITEM7_LOCATION, ITEM7_POSITION);
                defaultGridConversion(ITEM9_LOCATION, ITEM9_POSITION);
                defaultGridConversion(ITEM13_LOCATION, ITEM13_POSITION);
                ON_CALL(*animator, isFinished()).WillByDefault(Return(true));
            }
        };

        TEST_F(AnimatedBoardView2Test, should_draw_nothing_when_created)
        {
            board.drawFrame();
        }
        
        TEST_F(AnimatedBoardView2Test, should_fail_when_added_item_has_invalid_id)
        {
            ASSERT_THROW(board.addItems({{INVALID_ID, {0, 0}}}), std::out_of_range);
        }
        
        TEST_F(AnimatedBoardView2Test, should_not_select_anything_when_position_is_not_valid)
        {
            Position POSITION{2, 3};
            EXPECT_CALL(*grid, isValid(POSITION)).WillRepeatedly(Return(false));

            board.selectItemAt(POSITION);

            ASSERT_TRUE(board.getSelectedItemLocations().empty());
        }

        TEST_F(AnimatedBoardView2Test, should_select_nothing_when_created)
        {
            ASSERT_TRUE(board.getSelectedItemLocations().empty());
        }
        
        TEST_F(AnimatedBoardView2Test, should_select_items_at_given_coordinates_based_on_grid)
        {
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
        
        TEST_F(AnimatedBoardView2Test, should_not_select_items_when_animator_is_animating)
        {
            EXPECT_CALL(*animator, isFinished()).WillRepeatedly(Return(false));
            
            board.selectItemAt(ITEM3_POSITION);

            ASSERT_TRUE(board.getSelectedItemLocations().empty());
        }
        
        TEST_F(AnimatedBoardView2Test, should_clear_selection)
        {
            board.selectItemAt(ITEM3_POSITION);
            board.selectItemAt(ITEM7_POSITION);
            board.clearSelection();
            
            ASSERT_TRUE(board.getSelectedItemLocations().empty());
        }

        TEST_F(AnimatedBoardView2Test, should_not_select_the_same_item_twice)
        {
            board.selectItemAt(ITEM3_POSITION);
            board.selectItemAt(ITEM3_POSITION);
            ASSERT_EQ(1u, board.getSelectedItemLocations().size());
        }
        
        TEST_F(AnimatedBoardView2Test, should_draw_items_then_the_selection)
        {
            board.selectItemAt(ITEM3_POSITION);
            board.selectItemAt(ITEM7_POSITION);

            EXPECT_CALL(*selection, drawAt(ITEM3_POSITION));
            EXPECT_CALL(*selection, drawAt(ITEM7_POSITION));
            
            board.drawFrame();
        }
        
        TEST_F(AnimatedBoardView2Test, should_swap_items)
        {
            EXPECT_CALL(*animator, addSwappingAnimation(ITEM3_POSITION, ITEM7_POSITION));

            board.swapItems(ITEM3_LOCATION, ITEM7_LOCATION);
        }
        
        TEST_F(AnimatedBoardView2Test, should_swap_and_swap_back_when_items_were_not_swapped)
        {
            InSequence order;
            EXPECT_CALL(*animator, addSwappingAnimation(ITEM3_POSITION, ITEM7_POSITION));
            EXPECT_CALL(*animator, addSwappingAnimation(ITEM7_POSITION, ITEM3_POSITION));
            
            board.dontSwapItems(ITEM3_LOCATION, ITEM7_LOCATION);
        }
        
        TEST_F(AnimatedBoardView2Test, should_remove_items)
        {
            EXPECT_CALL(*animator, addDisappearingAnimation(Positions{ITEM3_POSITION, ITEM7_POSITION}));
            
            board.removeItems({ITEM3_LOCATION, ITEM7_LOCATION});
        }
        
        TEST_F(AnimatedBoardView2Test, should_move_items)
        {
            EXPECT_CALL(*animator, addMovingAnimation(SpriteMovements{{ITEM3_POSITION, ITEM7_POSITION}, {ITEM9_POSITION, ITEM13_POSITION}}));
            
            board.moveItems({{ITEM3_LOCATION, ITEM7_LOCATION}, {ITEM9_LOCATION, ITEM13_LOCATION}});
        }
    }
}
