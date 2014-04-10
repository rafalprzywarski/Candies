#include <GameRunner/GameRunner.hpp>
#include "MockGameLogic.hpp"
#include "MockEventDispatcher.hpp"
#include "MockTimer.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    struct GameRunnerTest : Test
    {
        Logic::MockGameLogicPtr gameLogic = std::make_shared<StrictMock<Logic::MockGameLogic> >();
        Logic::MockTimerPtr timer = std::make_shared<StrictMock<Logic::MockTimer>>();
        UI::MockEventDispatcherPtr eventDispatcher = std::make_shared<StrictMock<UI::MockEventDispatcher>>();
        GameRunner runner{gameLogic, timer, eventDispatcher};
    };
    
   
    TEST_F(GameRunnerTest, should_start_the_game_run_the_timer_and_dispatch_events_until_finished)
    {
        InSequence order;
        EXPECT_CALL(*gameLogic, start());
        EXPECT_CALL(*timer, start());
        EXPECT_CALL(*eventDispatcher, dispatch());
        EXPECT_CALL(*eventDispatcher, isFinished()).WillOnce(Return(false));
        EXPECT_CALL(*eventDispatcher, dispatch());
        EXPECT_CALL(*eventDispatcher, isFinished()).WillOnce(Return(false));
        EXPECT_CALL(*eventDispatcher, dispatch());
        EXPECT_CALL(*eventDispatcher, isFinished()).WillOnce(Return(true));
        
        runner.run();
    }
}
