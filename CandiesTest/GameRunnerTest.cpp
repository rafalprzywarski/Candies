#include <GameRunner/GameRunner.hpp>
#include "MockGameLogic.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    struct GameRunnerTest : Test
    {
        GameCore::MockGameLogicPtr gameLogic = std::make_shared<StrictMock<GameCore::MockGameLogic> >();
        GameRunner runner{gameLogic};
    };
    
    TEST_F(GameRunnerTest, should_start_the_game)
    {
        EXPECT_CALL(*gameLogic, start());
        runner.run();
    }
}