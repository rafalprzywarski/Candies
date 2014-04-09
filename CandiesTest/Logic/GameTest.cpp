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

        typedef std::vector<ItemId> ItemIds;

        struct GameTest : Test
        {
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

        struct FailingExample
        {
            std::string name;
            ItemIds board;
            Location from;
            Location to;
        };
        
        std::ostream& operator<<(std::ostream& os, const FailingExample& example)
        {
            return os << example.name;
        }

        struct SuccessfulExample
        {
            std::string name;
            ItemIds board;
            Location from;
            Location to;
            Locations removed;
            ItemIds added;
        };
        
        std::ostream& operator<<(std::ostream& os, const SuccessfulExample& example)
        {
            return os << example.name;
        }
        
        Location From(Location l) { return l; }
        Location To(Location l) { return l; }
        Locations Removed(Locations l) { return l; }
        ItemIds Added(ItemIds l) { return l; }

        struct GameFailingSwappingTest : GameTest, WithParamInterface<FailingExample> {};
        
        TEST_P(GameFailingSwappingTest, should_not_swap)
        {
            setBoard(GetParam().board);
            Board initialBoard = game->getBoard();
            
            game->swapItems(GetParam().from, GetParam().to);
            
            ASSERT_TRUE(initialBoard == game->getBoard());
        }
        
        INSTANTIATE_TEST_CASE_P(
            Examples, GameFailingSwappingTest,
            Values(
                FailingExample{
                    "not neighbours",
                    {
                        4,2,3,0,0,1,3,1,
                        3,3,0,4,1,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({2, 2}), To({2, 4})},
                FailingExample{
                    "not neighbours, reverse",
                    {
                        4,2,3,0,0,1,3,1,
                        3,3,0,4,1,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({2, 4}), To({2, 2})},
                FailingExample{
                    "2 horizontal right",
                    {
                        4,2,3,0,0,1,3,1,
                        3,3,0,4,1,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({4, 1}), To({4, 0})},
                FailingExample{
                    "2 horizontal right, reverse",
                    {
                        4,2,3,0,0,1,3,1,
                        3,3,0,4,1,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({4, 0}), To({4, 1})},
                                FailingExample{
                    "2 horizontal left",
                    {
                        4,2,3,1,0,2,3,1,
                        3,3,0,4,1,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({4, 1}), To({4, 0})},
                FailingExample{
                    "2 horizontal left, reverse",
                    {
                        4,2,3,1,0,2,3,1,
                        3,3,0,4,1,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({4, 0}), To({4, 1})}

            )
        );


        struct GameSuccessfulSwappingTest : GameTest, WithParamInterface<SuccessfulExample> {};
        
        TEST_P(GameSuccessfulSwappingTest, should_replace_3_aligned_items_with_3_new_items)
        {
            ASSERT_EQ(GetParam().added.size(), GetParam().removed.size()) << "must add and remove the same number of elements";

            setBoard(GetParam().board);
            expectGenerationOf(GetParam().added);
            
            Expectation swapping = EXPECT_CALL(*observer, itemsSwapped(GetParam().from, GetParam().to));
            ExpectationSet removal;
            for (auto loc : GetParam().removed)
                removal += EXPECT_CALL(*observer, itemRemoved(loc)).After(swapping);
            for (std::size_t i = 0; i < GetParam().added.size(); ++i)
                EXPECT_CALL(*observer, itemAdded(GetParam().added[i], GetParam().removed[i])).After(removal);
            
            game->swapItems(GetParam().from, GetParam().to);
        }

        INSTANTIATE_TEST_CASE_P(
            Examples, GameSuccessfulSwappingTest,
            Values(
                SuccessfulExample{
                    "3 horizontal right",
                    {
                        3,4,4,0,0,1,3,1,
                        3,3,0,4,1,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({3, 0}), To({3, 1}),
                    Removed({{1, 0}, {2, 0}, {3, 0}}),
                    Added({1, 2, 3})},
                SuccessfulExample{
                    "3 horizontal middle",
                    {
                        3,2,4,0,4,1,3,1,
                        3,3,0,4,1,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({3, 0}), To({3, 1}),
                    Removed({{2, 0}, {3, 0}, {4, 0}}),
                    Added({1, 2, 3})},
                SuccessfulExample{
                    "3 horizontal left",
                    {
                        3,2,2,0,4,4,3,1,
                        3,3,0,4,1,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({3, 0}), To({3, 1}),
                    Removed({{3, 0}, {4, 0}, {5, 0}}),
                    Added({1, 2, 3})},
                SuccessfulExample{
                    "5 horizontal middle",
                    {
                        3,4,4,0,4,4,3,4,
                        3,3,2,4,2,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({3, 0}), To({3, 1}),
                    Removed({{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}}),
                    Added({0, 1, 2, 3, 4})},
                SuccessfulExample{
                    "5 horizontal middle, reverse swap",
                    {
                        3,4,4,0,4,4,3,4,
                        3,3,2,4,2,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({3, 1}), To({3, 0}),
                    Removed({{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}}),
                    Added({0, 1, 2, 3, 4})}
            )
        );
    }
}
