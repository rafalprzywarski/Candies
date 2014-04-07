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
        
        TEST(BoardTest, equality_comparison_should_compare_sizes)
        {
            EXPECT_TRUE(Board(2, 3) == Board(2, 3));
            EXPECT_FALSE(Board(2, 7) == Board(2, 3));
            EXPECT_FALSE(Board(7, 3) == Board(2, 3));
        }
        
        TEST(BoardTest, equality_comparison_should_compare_items)
        {
            Board b1{2, 2}, b2{2, 2};
            ASSERT_TRUE(b1 == b2);
            b1[{0, 0}] = 3;
            ASSERT_FALSE(b1 == b2);
            b1 = b2; b1[{0, 1}] = 3;
            ASSERT_FALSE(b1 == b2);
            b1 = b2; b1[{1, 0}] = 3;
            ASSERT_FALSE(b1 == b2);
            b1 = b2; b1[{1, 0}] = 3;
            ASSERT_FALSE(b1 == b2);
        }
    }
}
