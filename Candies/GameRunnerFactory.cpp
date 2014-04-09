#include "GameRunnerFactory.hpp"
#include "SDLGameUI.hpp"
#include "SDLEventDispatcher.hpp"
#include <GameRunner/GameRunner.hpp>
#include <Logic/GameFactory.hpp>
#include "MouseItemSelector.hpp"
#include "SDLRendererFactory.hpp"
#include "SDLSprite.hpp"
#include "StaticBoardView.hpp"
#include <Logic/StdItemGenerator.hpp>

namespace Candies
{
    class BoardUpdater : public Candies::Logic::GameObserver
    {
    public:
        BoardUpdater(UI::StaticBoardViewPtr board) : board(board) { }
        virtual void itemAdded(Candies::Logic::ItemId item, Candies::Logic::Location loc)
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
        auto itemGenerator = std::make_shared<Candies::Logic::StdItemGenerator>(gems.size());
        auto gameObserver = std::make_shared<BoardUpdater>(board);
        auto gameLogic = Candies::Logic::GameFactory().createGame(itemGenerator, gameObserver);
        auto mouseItemSelector = std::make_shared<Candies::UI::MouseItemSelector>(board, gameLogic);
        auto dispatcher = std::make_shared<Candies::UI::SDLEventDispatcher>(ui, mouseItemSelector);
        auto runner = std::make_shared<Candies::GameRunner>(gameLogic, dispatcher);
        return runner;
    }
}
