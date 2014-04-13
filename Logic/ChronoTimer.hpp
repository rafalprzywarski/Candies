#pragma once
#include "Timer.hpp"
#include <chrono>

namespace Candies
{
    namespace Logic
    {
        class ChronoTimer : public Timer
        {
        public:
            ChronoTimer(std::chrono::seconds time) : time(time) { }
            virtual void start();
            virtual int getTime() const;
        private:
            std::chrono::seconds time;
            std::chrono::steady_clock::time_point to;
        };
    }
}
