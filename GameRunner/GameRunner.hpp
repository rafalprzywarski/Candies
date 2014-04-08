#pragma once
#include <GameCore/GameLogic.hpp>

namespace Candies
{
    class GameRunner
    {
    public:
        GameRunner(GameCore::GameLogicPtr logic) : logic(logic) { }
        void run();
    private:
        GameCore::GameLogicPtr logic;
    };
}
