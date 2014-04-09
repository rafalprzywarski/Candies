#include <Logic/GameFactory.hpp>
#include "MockItemGenerator.hpp"
#include "MockGameObserver.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace Logic
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
            MockGameObserverPtr observer = std::make_shared<NiceMock<MockGameObserver>>();
            GamePtr game = GameFactory().createGame(itemGenerator, observer);
            ItemIds ALL_ITEMS = {
                4,2,3,0,0,1,3,1,
                3,3,0,4,1,4,4,0,
                2,0,4,0,2,0,2,3,
                4,1,4,1,4,2,4,4,
                1,2,2,3,4,0,4,0,
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
            
            void expectItemAddedNotificationsFor(ItemIds items)
            {
                for (unsigned y = 0; y < BOARD_HEIGHT; ++y)
                    for (unsigned x = 0; x < BOARD_WIDTH; ++x)
                        EXPECT_CALL(*observer, itemAdded(ALL_ITEMS[x + y * BOARD_WIDTH], Location(x, y)));
            }
            
            void setBoard(ItemIds items)
            {
                expectGenerationOf(items);
                game->start();
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

        TEST_F(GameTest, should_notify_observer_about_filling_the_board_with_generated_items_when_game_is_started)
        {
            expectGenerationOf(ALL_ITEMS);
            expectItemAddedNotificationsFor(ALL_ITEMS);
            game->start();
        }

        TEST_F(GameTest, should_not_swap_items_between_two_given_location_when_they_are_not_neighbours)
        {
            setBoard({
                4,2,3,0,0,1,3,1,
                3,3,0,4,1,4,4,0,
                2,0,4,0,2,0,2,3,
                4,1,4,1,4,2,4,4,
                1,2,2,3,4,0,4,0,
                2,3,4,1,1,0,1,4,
                3,1,4,2,4,1,1,0,
                1,4,3,2,1,3,3,2 });
            Board initialBoard = game->getBoard();
            
            game->swapItems({2, 2}, {2, 4});
            
            ASSERT_TRUE(initialBoard == game->getBoard());
        }

        TEST_F(GameTest, should_replace_3_aligned_items_with_3_new_items)
        {
            setBoard({
                3,4,4,0,0,1,3,1,
                3,3,0,4,1,4,4,0,
                2,0,4,0,2,0,2,3,
                4,1,4,1,4,2,4,4,
                1,2,2,3,4,0,4,0,
                2,3,4,1,1,0,1,4,
                3,1,4,2,4,1,1,0,
                1,4,3,2,1,3,3,2 });
            
            expectGenerationOf({1, 2, 3});
            Expectation swapping = EXPECT_CALL(*observer, itemsSwapped(Location(3, 0), Location(3, 1)));
            ExpectationSet removal;
            removal += EXPECT_CALL(*observer, itemRemoved(Location(1, 0))).After(swapping);
            removal += EXPECT_CALL(*observer, itemRemoved(Location(2, 0))).After(swapping);
            removal += EXPECT_CALL(*observer, itemRemoved(Location(3, 0))).After(swapping);
            EXPECT_CALL(*observer, itemAdded(1, Location(1, 0))).After(removal);
            EXPECT_CALL(*observer, itemAdded(2, Location(2, 0))).After(removal);
            EXPECT_CALL(*observer, itemAdded(3, Location(3, 0))).After(removal);
            game->swapItems({3, 0}, {3, 1});
            
            expectBoardWith({
                3,1,2,3,0,1,3,1,
                3,3,0,0,1,4,4,0,
                2,0,4,0,2,0,2,3,
                4,1,4,1,4,2,4,4,
                1,2,2,3,4,0,4,0,
                2,3,4,1,1,0,1,4,
                3,1,4,2,4,1,1,0,
                1,4,3,2,1,3,3,2 });
        }
    }
}
