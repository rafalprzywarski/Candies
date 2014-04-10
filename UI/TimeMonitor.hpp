#pragma once
#include <Logic/Timer.hpp>
#include "Label.hpp"
#include "Switch.hpp"
#include "FrameUpdateListener.hpp"
#include <memory>

namespace Candies
{
    namespace UI
    {
        class TimeMonitor : public FrameUpdateListener
        {
        public:
            TimeMonitor(Logic::TimerPtr timer, LabelPtr label, SwitchPtr switch_)
            : timer(timer), label(label), switch_(switch_) { }
            virtual void update();
        private:
            Logic::TimerPtr timer;
            LabelPtr label;
            SwitchPtr switch_;
        };
    }
}
