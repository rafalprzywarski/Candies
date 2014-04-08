#pragma once
#include <GameCore/GameLogic.hpp>
#include <GameUI/EventDispatcher.hpp>

namespace Candies
{
    class GameRunner
    {
    public:
        GameRunner(GameCore::GameLogicPtr logic, UI::EventDispatcherPtr eventDispatcher)
            : logic(logic), eventDispatcher(eventDispatcher) { }
        void run();
    private:
        GameCore::GameLogicPtr logic;
        UI::EventDispatcherPtr eventDispatcher;
    };
}
