#include "GameRunner.hpp"

namespace Candies
{
    void GameRunner::run()
    {
        logic->start();
        do
        {
            eventDispatcher->dispatch();
        } while (!eventDispatcher->isFinished());
    }
}