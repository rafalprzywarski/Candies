#include "TimeMonitor.hpp"
#include <sstream>

namespace Candies
{
    namespace UI
    {
        void TimeMonitor::update()
        {
            std::ostringstream time;
            time << timer->getTime();
            label->setText(time.str());
        }
    }
}
