#include <GameCore/GameFactory.hpp>
#include "MockItemGenerator.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace GameCore
    {
        MATCHER_P2(HasSize, width, height, "has size " + PrintToString(width) + " x " + PrintToString(height))
        {
            return arg.getWidth() == width && arg.getHeight() == height;
        }
        
        MATCHER_P(IsFilledWith, items, "is filled with " + PrintToString(items))
        {
            for (unsigned y = 0; y < arg.getHeight(); ++y)
                for (unsigned x = 0; x < arg.getWidth(); ++x)
                    if (items.at(x + y * arg.getWidth()) != arg[{x, y}])
                        return false;
            return true;
        }

        struct GameTest : Test
        {
            typedef std::vector<ItemId> ItemIds;
            
            const unsigned BOARD_WIDTH = 8, BOARD_HEIGHT = 8;
            
            MockItemGeneratorPtr itemGenerator = std::make_shared<StrictMock<MockItemGenerator>>();
            GamePtr game = GameFactory().createGame(itemGenerator);
            ItemIds ALL_ITEMS = {
                4,2,3,0,0,1,3,1,
                3,3,0,4,1,4,4,0,
                2,0,4,0,2,0,2,3,
                4,1,4,1,4,4,4,4,
                1,2,2,1,4,0,4,0,
                2,3,4,1,1,0,1,4,
                3,1,4,2,4,1,1,0,
                1,4,3,2,1,3,3,2 };
            
            void expectGenerationOf(ItemIds items)
            {
                InSequence seq;
                for (auto item : items)
                    EXPECT_CALL(*itemGenerator, generate()).WillOnce(Return(item)).RetiresOnSaturation();
            }
            
            void expectBoardWith(ItemIds items)
            {
                Board expectedBoard{BOARD_WIDTH, BOARD_HEIGHT};
                ASSERT_EQ(BOARD_WIDTH * BOARD_HEIGHT, items.size());
                
                for (unsigned y = 0; y < expectedBoard.getHeight(); ++y)
                    for (unsigned x = 0; x < expectedBoard.getWidth(); ++x)
                        expectedBoard[{x, y}] = items.at(x + y * expectedBoard.getWidth());

                ASSERT_EQ(expectedBoard, game->getBoard());
            }
        };
        
        TEST_F(GameTest, board_should_be_filled_with_generated_items_when_game_is_started)
        {
            expectGenerationOf(ALL_ITEMS);
            game->start();
            auto board = game->getBoard();
            EXPECT_THAT(board, HasSize(BOARD_WIDTH, BOARD_HEIGHT));
            EXPECT_THAT(board, IsFilledWith(ALL_ITEMS));
        }
        
        TEST_F(GameTest, should_not_swap_items_between_two_given_location_when_they_are_not_neighbours)
        {
            expectGenerationOf({
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,2,0,0,0,
                0,1,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0 });
            game->start();
            Board oldBoard = game->getBoard();
            
            game->swapItems({1, 3}, {4, 2});
            
            ASSERT_TRUE(oldBoard == game->getBoard());
        }

        TEST_F(GameTest, should_swap_items_between_two_given_location_when_it_causes_three_items_to_be_aligned_in_a_row)
        {
            expectGenerationOf({
                0,0,0,0,0,0,0,0,
                0,0,0,1,0,0,0,0,
                0,1,1,2,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0 });
            game->start();
            
            game->swapItems({3, 2}, {3, 1});
            
            expectBoardWith({
                0,0,0,0,0,0,0,0,
                0,0,0,2,0,0,0,0,
                0,1,1,1,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0 });
        }
    }
}
