#include <GameUI/StaticBoard.hpp>
#include "MockSprite.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct StaticBoardTest : Test
        {
            MockSpritePtr item3 = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr item7 = std::make_shared<StrictMock<MockSprite>>();
            const int GRID_SIZE = 9;
            const Position POSITION = { 23, -17 };
            StaticBoard board{{{3, item3}, {7, item7}}, GRID_SIZE, POSITION};
        };

        TEST_F(StaticBoardTest, should_display_nothing_when_created)
        {
            board.update();
        }
        
        TEST_F(StaticBoardTest, should_display_added_items_according_to_board_position_and_grid_size)
        {
            board.addItem(3, {0, 0});
            board.addItem(7, {3, 2});
            EXPECT_CALL(*item3, drawAt(Position(POSITION.x, POSITION.y)));
            EXPECT_CALL(*item7, drawAt(Position(POSITION.x + 3 * GRID_SIZE, POSITION.y + 2 * GRID_SIZE)));
            
            board.update();
        }
    }
}
