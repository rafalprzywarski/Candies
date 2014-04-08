#include "GameRunnerFactory.hpp"
#include "SDLGameUI.hpp"
#include "SDLEventDispatcher.hpp"
#include <GameRunner/GameRunner.hpp>
#include <GameCore/GameFactory.hpp>
#include "StubItemGenerator.hpp"
#include "StubMouseEventListener.hpp"

namespace Candies
{
    struct StubGameObserver : public Candies::GameCore::GameObserver
    {
        virtual void itemAdded(Candies::GameCore::ItemId item, Candies::GameCore::Location loc) { }
    };

    GameRunnerPtr GameRunnerFactory::createRunner()
    {
        auto ui = std::make_shared<Candies::UI::SDLGameUI>();
        auto mouseEventListener = std::make_shared<Candies::UI::StubMouseEventListener>();
        auto dispatcher = std::make_shared<Candies::UI::SDLEventDispatcher>(ui, mouseEventListener);
        auto itemGenerator = std::make_shared<Candies::GameCore::StubItemGenerator>();
        auto gameObserver = std::make_shared<StubGameObserver>();
        auto gameLogic = Candies::GameCore::GameFactory().createGame(itemGenerator, gameObserver);
        auto runner = std::make_shared<Candies::GameRunner>(gameLogic, dispatcher);
        return runner;
    }
}
