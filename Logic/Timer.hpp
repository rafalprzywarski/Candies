#pragma once
#include <memory>

namespace Candies
{
    namespace Logic
    {
        class Timer
        {
        public:
            virtual ~Timer() { }
            virtual void start() = 0;
            virtual int getTime() const = 0;
        };
        
        typedef std::shared_ptr<Timer> TimerPtr;
    }
}
