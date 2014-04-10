#include <Logic/GameFactory.hpp>
#include "MockItemGenerator.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace Logic
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
            Board board{2, 3};
            board[{0, 1}] = 3;
            board[{1, 0}] = 7;
            board[{1, 2}] = 5;
            ASSERT_TRUE((3 == Const(board)[{0, 1}]));
            ASSERT_TRUE((7 == Const(board)[{1, 0}]));
            ASSERT_TRUE((5 == Const(board)[{1, 2}]));
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
        
        TEST(BoardTest, should_fail_when_accessed_out_of_bounds)
        {
            Board b{2, 3};
            ASSERT_THROW((b[{3, 0}]), std::out_of_range);
            ASSERT_THROW((b[{4, 0}]), std::out_of_range);
            ASSERT_THROW((b[{0, 4}]), std::out_of_range);
            ASSERT_THROW((b[{0, 5}]), std::out_of_range);
        }
        
        TEST(BoardTest, should_count_items_with_given_id_in_negative_direction_from_x)
        {
            Board b{5, 4};
            ASSERT_EQ(0, b.countAlignedInNegativeDirection<&Location::x>({0, 1}, 3));
            b[{2, 1}] = 3;
            ASSERT_EQ(1, b.countAlignedInNegativeDirection<&Location::x>({3, 1}, 3));
            b[{3, 1}] = 3;
            ASSERT_EQ(1, b.countAlignedInNegativeDirection<&Location::x>({3, 1}, 3));
            b[{1, 1}] = 3;
            ASSERT_EQ(2, b.countAlignedInNegativeDirection<&Location::x>({3, 1}, 3));
            b[{0, 1}] = 3;
            ASSERT_EQ(3, b.countAlignedInNegativeDirection<&Location::x>({3, 1}, 3));
        }

        TEST(BoardTest, should_count_items_with_given_id_in_negative_direction_from_y)
        {
            Board b{4, 5};
            ASSERT_EQ(0, b.countAlignedInNegativeDirection<&Location::y>({1, 0}, 3));
            b[{1, 2}] = 3;
            ASSERT_EQ(1, b.countAlignedInNegativeDirection<&Location::y>({1, 3}, 3));
            b[{1, 3}] = 3;
            ASSERT_EQ(1, b.countAlignedInNegativeDirection<&Location::y>({1, 3}, 3));
            b[{1, 1}] = 3;
            ASSERT_EQ(2, b.countAlignedInNegativeDirection<&Location::y>({1, 3}, 3));
            b[{1, 0}] = 3;
            ASSERT_EQ(3, b.countAlignedInNegativeDirection<&Location::y>({1, 3}, 3));
        }

        TEST(BoardTest, should_count_items_with_given_id_in_positive_direction_from_x)
        {
            Board b{5, 4};
            ASSERT_EQ(0, b.countAlignedInPositiveDirection<&Location::x>({4, 1}, 3));
            b[{2, 1}] = 3;
            ASSERT_EQ(1, b.countAlignedInPositiveDirection<&Location::x>({1, 1}, 3));
            b[{1, 1}] = 3;
            ASSERT_EQ(1, b.countAlignedInPositiveDirection<&Location::x>({1, 1}, 3));
            b[{3, 1}] = 3;
            ASSERT_EQ(2, b.countAlignedInPositiveDirection<&Location::x>({1, 1}, 3));
            b[{4, 1}] = 3;
            ASSERT_EQ(3, b.countAlignedInPositiveDirection<&Location::x>({1, 1}, 3));
        }
        
        TEST(BoardTest, should_count_items_with_given_id_in_positive_direction_from_y)
        {
            Board b{4, 5};
            ASSERT_EQ(0, b.countAlignedInPositiveDirection<&Location::y>({1, 4}, 3));
            b[{1, 2}] = 3;
            ASSERT_EQ(1, b.countAlignedInPositiveDirection<&Location::y>({1, 1}, 3));
            b[{1, 1}] = 3;
            ASSERT_EQ(1, b.countAlignedInPositiveDirection<&Location::y>({1, 1}, 3));
            b[{1, 3}] = 3;
            ASSERT_EQ(2, b.countAlignedInPositiveDirection<&Location::y>({1, 1}, 3));
            b[{1, 4}] = 3;
            ASSERT_EQ(3, b.countAlignedInPositiveDirection<&Location::y>({1, 1}, 3));
        }
        
        TEST(BoardTest, should_swap_items_between_given_locations)
        {
            Board b{3, 3};
            const Location LOC1{1, 2}, LOC2{0, 1};
            b[LOC1] = 7;
            b[LOC2] = 4;
            b.swapItems(LOC1, LOC2);
            ASSERT_EQ(4, b[LOC1]);
            ASSERT_EQ(7, b[LOC2]);
        }
        
    }
}
