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
            EXPECT_CALL(*timer, getTime()).WillRepeatedly(Return(55));
            EXPECT_CALL(*label, setText("55"));
            monitor.update();
        }
    }
}
