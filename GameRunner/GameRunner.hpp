#pragma once
#include <GameCore/GameLogic.hpp>
#include <UI/EventDispatcher.hpp>

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
    
    typedef std::shared_ptr<GameRunner> GameRunnerPtr;
}
