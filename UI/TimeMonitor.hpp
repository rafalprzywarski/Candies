#pragma once
#include <Logic/Timer.hpp>
#include "Label.hpp"
#include "Switch.hpp"
#include "UpdateFrameListener.hpp"
#include <memory>

namespace Candies
{
    namespace UI
    {
        class TimeMonitor : public UpdateFrameListener
        {
        public:
            TimeMonitor(Logic::TimerPtr timer, LabelPtr label, SwitchPtr switch_)
            : timer(timer), label(label), switch_(switch_) { }
            virtual void updateFrame();
        private:
            Logic::TimerPtr timer;
            LabelPtr label;
            SwitchPtr switch_;
            std::string toString(int n);
        };
    }
}
