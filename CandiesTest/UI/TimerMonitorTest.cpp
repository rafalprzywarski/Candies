#include <UI/TimeMonitor.hpp>
#include "MockTimer.hpp"
#include "MockLabel.hpp"
#include "MockSwitch.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct TimeMonitorTest : Test
        {
            Logic::MockTimerPtr timer = std::make_shared<StrictMock<Logic::MockTimer>>();
            MockLabelPtr label = std::make_shared<StrictMock<MockLabel>>();
            MockSwitchPtr switch_ = std::make_shared<StrictMock<MockSwitch>>();
            TimeMonitor monitor{timer, label, switch_};
        };
        
        TEST_F(TimeMonitorTest, should_update_the_time_on_the_label)
        {
            EXPECT_CALL(*timer, getTime()).WillOnce(Return(55));
            EXPECT_CALL(*label, setText("55"));
            monitor.updateFrame();
        }
        
        TEST_F(TimeMonitorTest, should_disable_the_switch_when_time_runs_out)
        {
            EXPECT_CALL(*timer, getTime()).WillOnce(Return(0));
            EXPECT_CALL(*label, setText(_));
            EXPECT_CALL(*switch_, disable());
            monitor.updateFrame();
        }
    }
}
