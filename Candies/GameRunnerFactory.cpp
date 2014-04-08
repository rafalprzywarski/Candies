#include "GameRunnerFactory.hpp"
#include "SDLGameUI.hpp"
#include "SDLEventDispatcher.hpp"
#include <GameRunner/GameRunner.hpp>
#include <GameCore/GameFactory.hpp>
#include "StubItemGenerator.hpp"
#include "StubMouseEventListener.hpp"
#include "SDLRendererFactory.hpp"
#include "SDLSprite.hpp"
#include "StaticBoard.hpp"

namespace Candies
{
    struct StubGameObserver : public Candies::GameCore::GameObserver
    {
        virtual void itemAdded(Candies::GameCore::ItemId item, Candies::GameCore::Location loc) { }
    };
    
    std::vector<std::pair<const GameCore::ItemId, UI::SpritePtr>> loadGems(std::shared_ptr<SDL_Renderer> renderer)
    {
        std::vector<std::string> files = { "Blue.png", "Green.png", "Purple.png", "Red.png", "Yellow.png" };
        std::vector<std::pair<const GameCore::ItemId, UI::SpritePtr>> gems;
        for (auto& file : files)
            gems.push_back({gems.size(), std::make_shared<UI::SDLSprite>(renderer, file)});
        return gems;
    }

    GameRunnerPtr GameRunnerFactory::createRunner()
    {
        auto const SCREEN_WIDTH = 755, SCREEN_HEIGHT = 600;
        auto const GRID_SIZE = 36;
        UI::Position BOARD_POSITION = { 20, 40 };

        auto renderer = UI::SDLRendererFactory().createRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);
        auto background = std::make_shared<UI::SDLSprite>(renderer, "BackGround.jpg");
        auto gems = loadGems(renderer);
        auto board = std::make_shared<UI::StaticBoard>(gems, GRID_SIZE, BOARD_POSITION);
        auto ui = std::make_shared<Candies::UI::SDLGameUI>(renderer, background, board);
        auto mouseEventListener = std::make_shared<Candies::UI::StubMouseEventListener>();
        auto dispatcher = std::make_shared<Candies::UI::SDLEventDispatcher>(ui, mouseEventListener);
        auto itemGenerator = std::make_shared<Candies::GameCore::StubItemGenerator>();
        auto gameObserver = std::make_shared<StubGameObserver>();
        auto gameLogic = Candies::GameCore::GameFactory().createGame(itemGenerator, gameObserver);
        auto runner = std::make_shared<Candies::GameRunner>(gameLogic, dispatcher);
        return runner;
    }
}
