#include "SynchronizedAnimationTimer.hpp"

namespace Candies
{
    namespace UI
    {
        SynchronizedAnimationTimer::SynchronizedAnimationTimer()
        : start(std::chrono::high_resolution_clock::now()), now(start)
        {
        }

        float SynchronizedAnimationTimer::getTime() const
        {
            using namespace std::chrono;
            return duration_cast<duration<float>>(now - start).count();
        }
        
        void SynchronizedAnimationTimer::updateFrame()
        {
            now = std::chrono::high_resolution_clock::now();
        }
    }
}
