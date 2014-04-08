#include <GameRunner/GameRunner.hpp>
#include "MockGameLogic.hpp"
#include "MockEventDispatcher.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    struct GameRunnerTest : Test
    {
        GameCore::MockGameLogicPtr gameLogic = std::make_shared<StrictMock<GameCore::MockGameLogic> >();
        UI::MockEventDispatcherPtr eventDispatcher = std::make_shared<StrictMock<UI::MockEventDispatcher>>();
        GameRunner runner{gameLogic, eventDispatcher};
    };
    
   
    TEST_F(GameRunnerTest, should_start_the_game_and_dispatch_events_until_finished)
    {
        InSequence order;
        EXPECT_CALL(*gameLogic, start());
        EXPECT_CALL(*eventDispatcher, dispatch());
        EXPECT_CALL(*eventDispatcher, isFinished()).WillOnce(Return(false));
        EXPECT_CALL(*eventDispatcher, dispatch());
        EXPECT_CALL(*eventDispatcher, isFinished()).WillOnce(Return(false));
        EXPECT_CALL(*eventDispatcher, dispatch());
        EXPECT_CALL(*eventDispatcher, isFinished()).WillOnce(Return(true));
        
        runner.run();
    }
}