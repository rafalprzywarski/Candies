#include "TimeMonitor.hpp"
#include <sstream>

namespace Candies
{
    namespace UI
    {
        void TimeMonitor::update()
        {
            auto time = timer->getTime();
            label->setText(toString(time));
            if (time == 0)
                switch_->disable();
        }
        
        std::string TimeMonitor::toString(int n)
        {
            std::ostringstream text;
            text << n;
            return text.str();
        }
    }
}
