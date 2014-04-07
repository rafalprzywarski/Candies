#include <GameCore/GameFactory.hpp>
#include "MockItemGenerator.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
namespace GameCore
{
    
TEST(GameTest, board_should_be_filled_with_generated_items_when_game_is_started)
{
    auto itemGenerator = std::make_shared<StrictMock<MockItemGenerator>>();
    auto game = GameFactory().createGame(itemGenerator);

    std::vector<ItemId> items = {
        4,2,3,0,0,1,3,1,
        3,3,0,4,1,4,4,0,
        2,0,4,0,2,0,2,3,
        4,1,4,1,4,4,4,4,
        1,2,2,1,4,0,4,0,
        2,3,4,1,1,0,1,4,
        3,1,4,2,4,1,1,0,
        1,4,3,2,1,3,3,2 };
    InSequence seq;
    for (auto item : items)
        EXPECT_CALL(*itemGenerator, generate()).WillOnce(Return(item)).RetiresOnSaturation();

    game->start();
    auto board = game->getBoard();
    ASSERT_EQ(8u, board.getWidth());
    ASSERT_EQ(8u, board.getHeight());
    for (unsigned y = 0; y < board.getHeight(); ++y)
        for (unsigned x = 0; x < board.getWidth(); ++x)
            ASSERT_EQ(items.at(x + y * board.getWidth()), board(x, y));
}

}
}
