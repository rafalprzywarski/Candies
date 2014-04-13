#include <UI/InfiniteGrid.hpp>
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct InfiniteGridTest : Test
        {
            typedef Logic::Location Location;
            InfiniteGrid identity{{0, 0}, 1};
            int const OX = -5, OY = 7, SIZE = 9;
            InfiniteGrid grid{{OX, OY}, SIZE};
        };
        
        TEST_F(InfiniteGridTest, should_convert_position_from_grid_to_world_coordinates)
        {
            ASSERT_EQ(Position(3, 4), identity.toPosition({3, 4}));
            
            ASSERT_EQ(Position(OX, OY), grid.toPosition({0, 0}));
            ASSERT_EQ(Position(OX + 5 * SIZE, OY + 7 * SIZE), grid.toPosition({5, 7}));
        }
        
        TEST_F(InfiniteGridTest, should_convert_position_from_world_to_grid_coordinates)
        {
            ASSERT_EQ(Location(2, 3), identity.toLocation({2, 3}));
            
            ASSERT_EQ(Location(0, 0), grid.toLocation({OX, OY}));
            ASSERT_EQ(Location(0, 0), grid.toLocation({OX + (SIZE - 1), OY}));
            ASSERT_EQ(Location(0, 0), grid.toLocation({OX, OY + (SIZE - 1)}));
            ASSERT_EQ(Location(5, 3), grid.toLocation(grid.toPosition({5, 3})));
        }
        
        TEST_F(InfiniteGridTest, should_report_position_with_coordinates_lower_that_origin_as_invalid)
        {
            ASSERT_TRUE(grid.isValid({OX + 1, OY}));
            ASSERT_TRUE(grid.isValid({OX, OY + 1}));
            ASSERT_TRUE(grid.isValid({OX, OY}));
            ASSERT_FALSE(grid.isValid({OX - 1, OY}));
            ASSERT_FALSE(grid.isValid({OX, OY - 1}));
        }
    }
}
