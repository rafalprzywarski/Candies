#include "GameRunnerFactory.hpp"
#include "SDLGameUI.hpp"
#include "SDLEventDispatcher.hpp"
#include <GameRunner/GameRunner.hpp>
#include <Logic/GameFactory.hpp>
#include "MouseItemSwapper.hpp"
#include "SDLRendererFactory.hpp"
#include "SDLSprite.hpp"
#include "AnimatedBoardView.hpp"
#include <SDLUI/SDLLabel.hpp>
#include <UI/TimeMonitor.hpp>
#include <Logic/ChronoTimer.hpp>
#include <Logic/StdItemGenerator.hpp>
#include <UI/InfiniteGrid.hpp>
#include <UI/InstantSpriteAnimator.hpp>
#include <UI/Background.hpp>

namespace Candies
{
    class BoardViewConnector : public Candies::Logic::GameObserver
    {
    public:
        BoardViewConnector(UI::AnimatedBoardViewPtr board) : board(board) { }
        virtual void itemsAdded(const Logic::ItemIdsWithLocations& items)
        {
            for (auto& item : items)
                board->addItem(item.item, item.location);
        }
        virtual void itemsSwapped(Logic::Location loc1, Logic::Location loc2)
        {
            board->swapItems(loc1, loc2);
        }
        virtual void itemsRemoved(const Logic::Locations& locs)
        {
            for (auto& loc : locs)
                board->removeItem(loc);
        }
        
        virtual void itemsMoved(const Logic::Movements& movements)
        {
            for (auto& m : movements)
                board->moveItem(m.from, m.to);
        }

    private:
        UI::AnimatedBoardViewPtr board;
    };
    
    UI::AnimatedBoardView::Sprites loadGems(std::shared_ptr<SDL_Renderer> renderer)
    {
        std::vector<std::string> files = { "Blue.png", "Green.png", "Purple.png", "Red.png", "Yellow.png" };
        UI::AnimatedBoardView::Sprites gems;
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
        std::chrono::seconds const GAME_TIME(60);

        auto renderer = UI::SDLRendererFactory().createRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);
        auto backgroundSprite = std::make_shared<UI::SDLSprite>(renderer, "BackGround.jpg");
        auto gems = loadGems(renderer);
        auto selectionMarker = std::make_shared<UI::SDLSprite>(renderer, "Selected.png");
        auto grid = std::make_shared<UI::InfiniteGrid>(BOARD_POSITION, GRID_SIZE);
        auto spriteAnimator = std::make_shared<UI::InstantSpriteAnimator>();
        auto board = std::make_shared<UI::AnimatedBoardView>(gems, selectionMarker, grid, spriteAnimator);
        auto timerLabel = std::make_shared<UI::SDLLabel>(renderer, FONT, FONT_SIZE, FONT_COLOR, TIMER_POSITION);
        auto background = std::make_shared<UI::Background>(backgroundSprite);
        UI::DrawFrameListeners uiElements = { background, board, timerLabel };
        auto ui = std::make_shared<Candies::UI::SDLGameUI>(renderer, uiElements);
        auto itemGenerator = std::make_shared<Candies::Logic::StdItemGenerator>(gems.size());
        auto gameObserver = std::make_shared<BoardViewConnector>(board);
        auto gameLogic = Candies::Logic::GameFactory().createGame(itemGenerator, gameObserver);
        auto mouseItemSwapper = std::make_shared<Candies::UI::MouseItemSwapper>(board, gameLogic);
        auto timer = std::make_shared<Logic::ChronoTimer>(GAME_TIME);
        auto timeMonitor = std::make_shared<UI::TimeMonitor>(timer, timerLabel, mouseItemSwapper);
        UI::UpdateFrameListeners updateListeners = { timeMonitor };
        auto dispatcher = std::make_shared<Candies::UI::SDLEventDispatcher>(updateListeners, ui, mouseItemSwapper);
        auto runner = std::make_shared<Candies::GameRunner>(gameLogic, timer, dispatcher);
        return runner;
    }
}
