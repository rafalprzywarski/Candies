#pragma once
#include <memory>

namespace Candies
{
    namespace UI
    {
        class TimedInterpolator
        {
        public:
            virtual ~TimedInterpolator() { }
            virtual int interpolate(int from, int to, float time) const = 0;
        };
        
        typedef std::shared_ptr<TimedInterpolator> TimedInterpolatorPtr;
    }
}
