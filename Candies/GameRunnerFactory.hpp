#pragma once
#include <GameRunner/GameRunner.hpp>

namespace Candies
{
    class GameRunnerFactory
    {
    public:
        GameRunnerPtr createRunner();
    };
}
