#include "GameRunnerFactory.hpp"
#include "SDLGameUI.hpp"
#include "SDLEventDispatcher.hpp"
#include <GameRunner/GameRunner.hpp>
#include <GameCore/GameFactory.hpp>
#include "StubMouseEventListener.hpp"
#include "SDLRendererFactory.hpp"
#include "SDLSprite.hpp"
#include "StaticBoardView.hpp"
#include <GameCore/StdItemGenerator.hpp>

namespace Candies
{
    class BoardUpdater : public Candies::GameCore::GameObserver
    {
    public:
        BoardUpdater(UI::StaticBoardViewPtr board) : board(board) { }
        virtual void itemAdded(Candies::GameCore::ItemId item, Candies::GameCore::Location loc)
        {
            board->addItem(item, loc);
        }
    private:
        UI::StaticBoardViewPtr board;
    };
    
    UI::StaticBoardView::Sprites loadGems(std::shared_ptr<SDL_Renderer> renderer)
    {
        std::vector<std::string> files = { "Blue.png", "Green.png", "Purple.png", "Red.png", "Yellow.png" };
        UI::StaticBoardView::Sprites gems;
        for (auto& file : files)
            gems.push_back({gems.size(), std::make_shared<UI::SDLSprite>(renderer, file)});
        return gems;
    }

    GameRunnerPtr GameRunnerFactory::createRunner()
    {
        auto const SCREEN_WIDTH = 755, SCREEN_HEIGHT = 600;
        auto const GRID_SIZE = 42;
        UI::Position BOARD_POSITION = { 330, 105 };

        auto renderer = UI::SDLRendererFactory().createRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);
        auto background = std::make_shared<UI::SDLSprite>(renderer, "BackGround.jpg");
        auto gems = loadGems(renderer);
        auto selectionMarker = std::make_shared<UI::SDLSprite>(renderer, "Selected.png");
        auto board = std::make_shared<UI::StaticBoardView>(gems, selectionMarker, GRID_SIZE, BOARD_POSITION);
        auto ui = std::make_shared<Candies::UI::SDLGameUI>(renderer, background, board);
        auto mouseEventListener = std::make_shared<Candies::UI::StubMouseEventListener>();
        auto dispatcher = std::make_shared<Candies::UI::SDLEventDispatcher>(ui, mouseEventListener);
        auto itemGenerator = std::make_shared<Candies::GameCore::StdItemGenerator>(gems.size());
        auto gameObserver = std::make_shared<BoardUpdater>(board);
        auto gameLogic = Candies::GameCore::GameFactory().createGame(itemGenerator, gameObserver);
        auto runner = std::make_shared<Candies::GameRunner>(gameLogic, dispatcher);
        return runner;
    }
}
