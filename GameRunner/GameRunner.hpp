#pragma once
#include <Logic/GameLogic.hpp>
#include <UI/EventDispatcher.hpp>

namespace Candies
{
    class GameRunner
    {
    public:
        GameRunner(Logic::GameLogicPtr logic, UI::EventDispatcherPtr eventDispatcher)
            : logic(logic), eventDispatcher(eventDispatcher) { }
        void run();
    private:
        Logic::GameLogicPtr logic;
        UI::EventDispatcherPtr eventDispatcher;
    };
    
    typedef std::shared_ptr<GameRunner> GameRunnerPtr;
}
