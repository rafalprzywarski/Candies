#include "GameRunnerFactory.hpp"
#include "SDLGameUI.hpp"
#include "SDLEventDispatcher.hpp"
#include <GameRunner/GameRunner.hpp>
#include <Logic/GameFactory.hpp>
#include "MouseItemSwapper.hpp"
#include "SDLRendererFactory.hpp"
#include "SDLSprite.hpp"
#include "StaticBoardView.hpp"
#include <SDLUI/SDLLabel.hpp>
#include <Logic/StdItemGenerator.hpp>

namespace Candies
{
    class BoardViewConnector : public Candies::Logic::GameObserver
    {
    public:
        BoardViewConnector(UI::StaticBoardViewPtr board) : board(board) { }
        virtual void itemAdded(Candies::Logic::ItemId item, Candies::Logic::Location loc)
        {
            board->addItem(item, loc);
        }
        virtual void itemsSwapped(Logic::Location loc1, Logic::Location loc2)
        {
            board->swapItems(loc1, loc2);
        }
        virtual void itemRemoved(Logic::Location loc)
        {
            board->removeItem(loc);
        }
        
        virtual void itemMoved(Logic::Location from, Logic::Location to)
        {
            board->moveItem(from, to);
        }

    private:
        UI::StaticBoardViewPtr board;
    };
    
    struct StubTimer : Logic::Timer
    {
        void start() { }
        int getTime() const { return 0; }
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
        std::string const FONT = "comicate.ttf";
        auto const FONT_SIZE = 60;
        SDL_Color FONT_COLOR = {230, 45, 25};
        UI::Position const TIMER_POSITION = { 80, 435 };

        auto renderer = UI::SDLRendererFactory().createRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);
        auto background = std::make_shared<UI::SDLSprite>(renderer, "BackGround.jpg");
        auto gems = loadGems(renderer);
        auto selectionMarker = std::make_shared<UI::SDLSprite>(renderer, "Selected.png");
        auto board = std::make_shared<UI::StaticBoardView>(gems, selectionMarker, GRID_SIZE, BOARD_POSITION);
        auto timerLabel = std::make_shared<UI::SDLLabel>(renderer, FONT, FONT_SIZE, FONT_COLOR, TIMER_POSITION);
        timerLabel->setText("60");
        auto ui = std::make_shared<Candies::UI::SDLGameUI>(renderer, background, board, timerLabel);
        auto itemGenerator = std::make_shared<Candies::Logic::StdItemGenerator>(gems.size());
        auto gameObserver = std::make_shared<BoardViewConnector>(board);
        auto gameLogic = Candies::Logic::GameFactory().createGame(itemGenerator, gameObserver);
        auto mouseItemSelector = std::make_shared<Candies::UI::MouseItemSwapper>(board, gameLogic);
        UI::FrameUpdateListeners frameListeners = { ui };
        auto dispatcher = std::make_shared<Candies::UI::SDLEventDispatcher>(frameListeners, mouseItemSelector);
        auto timer = std::make_shared<StubTimer>();
        auto runner = std::make_shared<Candies::GameRunner>(gameLogic, timer, dispatcher);
        return runner;
    }
}
