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

        struct GameAcceptanceTest : Test
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
            
            GameAcceptanceTest()
            {
                ON_CALL(*itemGenerator, generate()).WillByDefault(Throw(std::out_of_range("too many")));
            }
            
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
            
            void expectItemsAddedNotificationFor(ItemIds items)
            {
                ItemIdsWithLocations expectedItems;
                for (unsigned y = 0; y < BOARD_HEIGHT; ++y)
                    for (unsigned x = 0; x < BOARD_WIDTH; ++x)
                        expectedItems.emplace_back(ALL_ITEMS[x + y * BOARD_WIDTH], Location(x, y));
                EXPECT_CALL(*observer, itemsAdded(expectedItems));
            }
            
            void setBoard(ItemIds items)
            {
                expectGenerationOf(items);
                game->start();
            }
            
            Expectation expectItemsMoved(std::vector<Movement> moves, ExpectationSet removal)
            {
                return EXPECT_CALL(*observer, itemsMoved(WhenSorted(sorted(moves)))).After(removal);
            }
            
            template <typename T>
            T sorted(T c)
            {
                std::sort(c.begin(), c.end());
                return std::move(c);
            }
            
            ItemIdsWithLocations merged(const ItemIds& ids, const Locations& locs)
            {
                ItemIdsWithLocations items;
                for (std::size_t i = 0; i != ids.size(); ++i)
                    items.emplace_back(ids[i], locs[i]);
                return items;
            }
        };
        
        TEST_F(GameAcceptanceTest, board_should_be_filled_with_generated_items_when_game_is_started)
        {
            expectGenerationOf(ALL_ITEMS);
            game->start();
            auto board = game->getBoard();
            EXPECT_THAT(board, HasSize(BOARD_WIDTH, BOARD_HEIGHT));
            EXPECT_THAT(board, IsFilledWith(ALL_ITEMS));
        }

        TEST_F(GameAcceptanceTest, should_notify_observer_about_filling_the_board_with_generated_items_when_game_is_started)
        {
            expectGenerationOf(ALL_ITEMS);
            expectItemsAddedNotificationFor(ALL_ITEMS);
            game->start();
        }
        
        TEST_F(GameAcceptanceTest, successful_swap_should_update_the_board)
        {
            setBoard({
                4,3,3,0,0,1,3,1,
                3,2,0,4,1,4,4,0,
                2,0,4,0,2,0,2,3,
                4,1,4,1,4,2,4,4,
                1,2,2,3,4,0,4,0,
                2,3,4,1,1,0,1,4,
                3,1,4,2,4,1,1,0,
                1,4,3,2,1,3,3,2 });
            expectGenerationOf({0, 0, 1});
            game->swapItems({0, 0}, {0, 1});
            
            expectBoardWith({
                0,0,1,0,0,1,3,1,
                4,2,0,4,1,4,4,0,
                2,0,4,0,2,0,2,3,
                4,1,4,1,4,2,4,4,
                1,2,2,3,4,0,4,0,
                2,3,4,1,1,0,1,4,
                3,1,4,2,4,1,1,0,
                1,4,3,2,1,3,3,2 });

            expectGenerationOf({1, 3, 1, 3, 1});
            game->swapItems({2, 0}, {2, 1});

            expectBoardWith({
                1,3,1,3,1,1,3,1,
                4,2,1,4,1,4,4,0,
                2,0,4,0,2,0,2,3,
                4,1,4,1,4,2,4,4,
                1,2,2,3,4,0,4,0,
                2,3,4,1,1,0,1,4,
                3,1,4,2,4,1,1,0,
                1,4,3,2,1,3,3,2 });
        }
        
        TEST_F(GameAcceptanceTest, items_should_fall_down_when_other_items_below_them_are_removed_and_new_items_should_be_added_above_them)
        {
            setBoard({
                4,3,3,0,0,1,3,1,
                2,2,0,1,2,4,4,0,
                2,1,1,0,1,0,2,3,
                4,1,4,1,4,2,4,4,
                1,2,2,3,4,0,4,0,
                2,3,4,4,1,4,1,4,
                3,1,4,2,4,1,1,0,
                1,4,3,2,1,3,3,2 });

            Expectation removal = EXPECT_CALL(*observer, itemsRemoved(SizeIs(5)));
            
            auto moving = expectItemsMoved({
                {{1, 1}, {1, 2}},
                {{1, 0}, {1, 1}},
                {{2, 1}, {2, 2}},
                {{2, 0}, {2, 1}},
                {{3, 0}, {3, 3}}}, removal);
                
            expectGenerationOf({1, 2, 3, 4, 3});
            EXPECT_CALL(*observer, itemsAdded(SizeIs(5))).After(moving);

            game->swapItems({4, 2}, {3, 2});

            expectBoardWith({
                4,1,2,3,0,1,3,1,
                2,3,3,4,2,4,4,0,
                2,2,0,3,0,0,2,3,
                4,1,4,0,4,2,4,4,
                1,2,2,3,4,0,4,0,
                2,3,4,4,1,4,1,4,
                3,1,4,2,4,1,1,0,
                1,4,3,2,1,3,3,2 });
        }

        TEST_F(GameAcceptanceTest, items_should_fall_to_the_bottom)
        {
            setBoard({
                4,3,3,0,0,1,3,2,
                2,2,0,1,2,4,4,3,
                2,1,1,0,1,0,2,1,
                4,1,4,1,4,2,1,3,
                1,2,2,3,4,0,4,2,
                2,3,4,4,1,4,3,4,
                3,1,4,2,4,1,1,3,
                1,4,3,2,1,3,2,3 });
            
            expectGenerationOf({8, 9, 8});
            game->swapItems({6, 5}, {7, 5});
            
            expectBoardWith({
                4,3,3,0,0,1,3,8,
                2,2,0,1,2,4,4,9,
                2,1,1,0,1,0,2,8,
                4,1,4,1,4,2,1,2,
                1,2,2,3,4,0,4,3,
                2,3,4,4,1,4,4,1,
                3,1,4,2,4,1,1,3,
                1,4,3,2,1,3,2,2 });
        }
        
        TEST_F(GameAcceptanceTest, falling_added_items_should_align_with_existing_ones)
        {
            setBoard({
                4,3,3,0,1,4,1,1,
                2,2,0,1,2,2,4,3,
                2,1,1,0,1,2,4,3,
                4,1,4,1,4,1,1,4,
                1,2,2,3,4,0,4,2,
                2,3,4,4,1,4,3,4,
                3,1,4,2,4,1,1,3,
                1,4,3,2,1,3,2,3 });
            
            
            expectGenerationOf({2, 3, 3, 1, 1, 2, 2, 1, 1});
            EXPECT_CALL(*observer, itemsSwapped(_, _));
            game->swapItems({4, 0}, {5, 0});
            
            expectBoardWith({
                4,3,3,0,4,1,3,2,
                2,2,0,1,2,1,4,1,
                2,1,1,0,1,2,4,1,
                4,1,4,1,4,1,1,4,
                1,2,2,3,4,0,4,2,
                2,3,4,4,1,4,3,4,
                3,1,4,2,4,1,1,3,
                1,4,3,2,1,3,2,3 });
        }
        
        TEST_F(GameAcceptanceTest, moved_items_should_align_with_existing_ones)
        {
            setBoard({
                4,3,3,0,1,4,1,1,
                2,2,0,1,4,2,4,3,
                2,0,2,1,2,2,4,3,
                4,1,4,3,4,1,1,4,
                1,2,2,3,4,0,4,2,
                2,3,4,4,1,4,3,4,
                3,1,4,2,4,1,1,3,
                1,4,3,2,1,3,2,3 });
            
            
            expectGenerationOf({1, 2, 3, 7, 8, 9});
            EXPECT_CALL(*observer, itemsSwapped(_, _));
            game->swapItems({2, 2}, {3, 2});
            
            expectBoardWith({
                4,3,3,1,7,3,1,1,
                2,2,0,0,8,4,4,3,
                2,0,1,1,9,2,4,3,
                4,1,4,3,2,1,1,4,
                1,2,2,3,1,0,4,2,
                2,3,4,4,1,4,3,4,
                3,1,4,2,4,1,1,3,
                1,4,3,2,1,3,2,3 });
        }

        TEST_F(GameAcceptanceTest, holes_cause_by_falling_items_are_handled_properly)
        {
            setBoard({
                4,3,2,1,2,4,1,1,
                2,2,8,1,8,3,4,3,
                2,0,2,2,1,3,4,3,
                4,1,8,1,8,1,1,4,
                1,3,2,1,2,0,4,2,
                2,3,4,4,1,4,3,4,
                3,1,4,2,4,1,1,3,
                1,4,3,2,1,3,2,3 });
            
            
            expectGenerationOf({2, 2, 2, 2, 2, 7, 9, 7, 9, 7, 9, 7, 9, 7, 9, 7 });
            EXPECT_CALL(*observer, itemsSwapped(_, _));
            game->swapItems({4, 2}, {3, 2});
            
            expectBoardWith({
                4,3,7,9,7,4,1,1,
                2,2,9,7,9,3,4,3,
                2,0,7,9,7,3,4,3,
                4,1,8,7,8,1,1,4,
                1,3,8,9,8,0,4,2,
                2,3,4,4,1,4,3,4,
                3,1,4,2,4,1,1,3,
                1,4,3,2,1,3,2,3 });
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

        struct GameFailedSwappingAcceptanceTest : GameAcceptanceTest, WithParamInterface<FailingExample> {};
        
        TEST_P(GameFailedSwappingAcceptanceTest, should_not_swap)
        {
            setBoard(GetParam().board);
            Board initialBoard = game->getBoard();
            
            EXPECT_CALL(*observer, itemsSwapped(_, _)).Times(0);
            EXPECT_CALL(*observer, itemsRemoved(_)).Times(0);
            EXPECT_CALL(*observer, itemsAdded(_)).Times(0);
            EXPECT_CALL(*observer, itemsMoved(_)).Times(0);
            game->swapItems(GetParam().from, GetParam().to);
            
            ASSERT_TRUE(initialBoard == game->getBoard());
        }
        
        INSTANTIATE_TEST_CASE_P(
            Examples, GameFailedSwappingAcceptanceTest,
            Values(
                FailingExample{
                    "not neighbours, vertical",
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
                    "not neighbours, vertical, reverse swap",
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
                    "not neighbours, horizontal",
                    {
                        4,4,3,0,4,1,3,1,
                        3,3,0,4,1,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({2, 0}), To({4, 0})},
                FailingExample{
                    "not neighbours, horizontal, reverse swap",
                    {
                        4,4,3,0,4,1,3,1,
                        3,3,0,4,1,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({4, 0}), To({2, 0})},
                FailingExample{
                    "not neighbours, touching corners",
                    {
                        4,4,3,0,4,1,3,1,
                        3,3,0,4,1,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({2, 0}), To({3, 1})},
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
                    From({4, 0}), To({4, 1})},
                FailingExample{
                    "no horizontal alignment left",
                    {
                        4,2,3,1,0,2,3,1,
                        3,3,0,4,1,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({0, 0}), To({0, 1})},
                FailingExample{
                    "no horizontal alignment left, margin 1",
                    {
                        3,2,2,1,0,2,3,1,
                        1,3,0,4,1,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({1, 0}), To({1, 1})},
                FailingExample{
                    "no horizontal alignment right",
                    {
                        4,2,3,1,0,2,3,1,
                        3,3,0,4,1,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({7, 0}), To({7, 1})},
                FailingExample{
                    "no horizontal alignment right, margin 1",
                    {
                        3,2,2,1,0,2,3,1,
                        1,3,0,4,1,4,1,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({6, 0}), To({6, 1})},
                FailingExample{
                    "2 horizontal, move to middle",
                    {
                        3,1,2,1,2,1,3,1,
                        1,3,0,4,1,4,1,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({2, 0}), To({3, 0})}
            )
        );


        struct GameSuccessfulSwappingAcceptanceTest : GameAcceptanceTest, WithParamInterface<SuccessfulExample> {};
        
        TEST_P(GameSuccessfulSwappingAcceptanceTest, should_replace_3_or_more_aligned_items_with_new_items)
        {
            ASSERT_EQ(GetParam().added.size(), GetParam().removed.size()) << "must add and remove the same number of elements";

            setBoard(GetParam().board);
            expectGenerationOf(GetParam().added);
            
            Expectation swapping = EXPECT_CALL(*observer, itemsSwapped(GetParam().from, GetParam().to));
            Expectation removal = EXPECT_CALL(*observer, itemsRemoved(WhenSorted(sorted(GetParam().removed)))).After(swapping);
            EXPECT_CALL(*observer, itemsMoved(_)).Times(0);
            auto expectedItems = sorted(merged(GetParam().added, GetParam().removed));
            EXPECT_CALL(*observer, itemsAdded(WhenSorted(expectedItems))).After(removal);
            
            game->swapItems(GetParam().from, GetParam().to);
        }

        INSTANTIATE_TEST_CASE_P(
            Examples, GameSuccessfulSwappingAcceptanceTest,
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
                    "3 horizontal, left horizontal move",
                    {
                        3,2,4,0,4,4,3,1,
                        3,3,0,2,1,4,4,0,
                        2,0,4,0,2,0,2,3,
                        4,1,4,1,4,2,4,4,
                        1,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({2, 0}), To({3, 0}),
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
                    Added({0, 1, 2, 3, 4})},
                SuccessfulExample{
                    "5 vertical middle",
                    {
                        3,1,4,0,4,4,3,4,
                        3,1,2,4,2,4,4,0,
                        2,3,4,0,2,0,2,3,
                        3,1,4,1,4,2,4,4,
                        3,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({0, 2}), To({1, 2}),
                    Removed({{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}}),
                    Added({0, 1, 2, 3, 4})},
                SuccessfulExample{
                    "5 vertical middle, reverse swap",
                    {
                        3,1,4,0,4,4,3,4,
                        3,1,2,4,2,4,4,0,
                        2,3,4,0,2,0,2,3,
                        3,1,4,1,4,2,4,4,
                        3,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({1, 2}), To({0, 2}),
                    Removed({{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}}),
                    Added({0, 1, 2, 3, 4})},
                SuccessfulExample{
                    "2x3 vertical swap",
                    {
                        3,1,4,2,4,0,3,4,
                        3,1,2,4,2,4,4,0,
                        2,3,4,0,2,0,2,3,
                        3,1,4,1,4,2,4,4,
                        3,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({3, 0}), To({3, 1}),
                    Removed({{2, 0}, {2, 1}, {3, 0}, {3, 1}, {4, 0}, {4, 1}}),
                    Added({0, 1, 2, 3, 4, 3})},
                SuccessfulExample{
                    "right angle",
                    {
                        1,3,1,1,4,0,3,4,
                        3,1,2,4,2,4,4,0,
                        2,1,4,0,2,0,2,3,
                        3,3,4,1,4,2,4,4,
                        3,2,2,3,4,0,4,0,
                        2,3,4,1,1,0,1,4,
                        3,1,4,2,4,1,1,0,
                        1,4,3,2,1,3,3,2 },
                    From({0, 0}), To({1, 0}),
                    Removed({{1, 0}, {1, 1}, {1, 2}, {2, 0}, {3, 0}}),
                    Added({0, 1, 2, 3, 4})}
            )
        );
    }
}
