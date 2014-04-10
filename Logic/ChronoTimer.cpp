#include "ChronoTimer.hpp"

namespace Candies
{
    namespace Logic
    {
        
        void ChronoTimer::start()
        {
            to = std::chrono::steady_clock::now() + time;
        }

        int ChronoTimer::getTime() const
        {
            using namespace std::chrono;
            auto now = steady_clock::now();
            auto currentTime = duration_cast<seconds>(to - now).count();
            return (currentTime < 0) ? 0 : int(currentTime);
        }
    }
}
