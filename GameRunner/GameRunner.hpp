#pragma once
#include <Logic/GameLogic.hpp>
#include <Logic/Timer.hpp>
#include <UI/EventDispatcher.hpp>

namespace Candies
{
    class GameRunner
    {
    public:
        GameRunner(Logic::GameLogicPtr logic, Logic::TimerPtr timer, UI::EventDispatcherPtr eventDispatcher)
            : logic(logic), timer(timer), eventDispatcher(eventDispatcher) { }
        void run();
    private:
        Logic::GameLogicPtr logic;
        Logic::TimerPtr timer;
        UI::EventDispatcherPtr eventDispatcher;
    };
    
    typedef std::shared_ptr<GameRunner> GameRunnerPtr;
}
