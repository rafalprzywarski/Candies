#include <GameCore/GameFactory.hpp>
#include "MockItemGenerator.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace GameCore
    {
        TEST(BoardTest, should_provide_size_accessors)
        {
            Board board{5, 3};
            ASSERT_EQ(5u, board.getWidth());
            ASSERT_EQ(3u, board.getHeight());
        }
        
        TEST(BoardTest, should_initialize_all_items_with_zeros)
        {
            Board board{2, 2};
            ASSERT_TRUE((0 == board[{0, 0}]));
            ASSERT_TRUE((0 == board[{1, 0}]));
            ASSERT_TRUE((0 == board[{1, 1}]));
        }
        
        TEST(BoardTest, should_provide_item_access)
        {
            Board board{2, 2};
            board[{0, 1}] = 3;
            ASSERT_TRUE((3 == Const(board)[{0, 1}]));
        }
    }
}
