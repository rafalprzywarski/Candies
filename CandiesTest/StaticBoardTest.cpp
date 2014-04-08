#include <GameUI/StaticBoard.hpp>
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct StaticBoardTest : Test
        {
            StaticBoard board;
        };

        TEST_F(StaticBoardTest, should_display_nothing_when_created)
        {
            board.update();
        }
    }
}
