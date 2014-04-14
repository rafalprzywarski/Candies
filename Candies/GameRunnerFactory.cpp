#include "GameRunnerFactory.hpp"
#include "SDLGameUI.hpp"
#include "SDLEventDispatcher.hpp"
#include <GameRunner/GameRunner.hpp>
#include <Logic/GameFactory.hpp>
#include "MouseItemSwapper.hpp"
#include "SDLRendererFactory.hpp"
#include "SDLSprite.hpp"
#include "AnimatedBoardView2.hpp"
#include <SDLUI/SDLLabel.hpp>
#include <UI/TimeMonitor.hpp>
#include <Logic/ChronoTimer.hpp>
#include <Logic/StdItemGenerator.hpp>
#include <UI/BoundedGrid.hpp>
#include <UI/Background.hpp>
#include <UI/StagedBoardAnimator.hpp>
#include <UI/SynchronizedAnimationTimer.hpp>
#include <UI/AnimationsFactory.hpp>

namespace Candies
{
    class BoardViewConnector : public Candies::Logic::GameObserver
    {
    public:
        BoardViewConnector(UI::AnimatedBoardView2Ptr board) : board(board) { }
        virtual void itemsAdded(const Logic::ItemIdsWithLocations& items)
        {
            board->addItems(items);
        }
        virtual void itemsSwapped(Logic::Location loc1, Logic::Location loc2)
        {
            board->swapItems(loc1, loc2);
        }
        virtual void itemsRemoved(const Logic::Locations& locs)
        {
            board->removeItems(locs);
        }
        
        virtual void itemsMoved(const Logic::Movements& movements)
        {
            board->moveItems(movements);
        }

    private:
        UI::AnimatedBoardView2Ptr board;
    };
    
    UI::AnimatedBoardView2::Sprites loadGems(std::shared_ptr<SDL_Renderer> renderer)
    {
        std::vector<std::string> files = { "Blue.png", "Green.png", "Purple.png", "Red.png", "Yellow.png" };
        UI::AnimatedBoardView2::Sprites gems;
        for (auto& file : files)
            gems.push_back({gems.size(), std::make_shared<UI::SDLSprite>(renderer, file)});
        return gems;
    }

    GameRunnerPtr GameRunnerFactory::createRunner()
    {
        auto const SCREEN_WIDTH = 755, SCREEN_HEIGHT = 600;
        auto const GRID_SIZE = 42, BOARD_WIDTH = 8, BOARD_HEIGHT = 8;
        UI::Position BOARD_POSITION = { 330, 105 };
        std::string const FONT = "comicate.ttf";
        auto const FONT_SIZE = 60;
        SDL_Color FONT_COLOR = {230, 45, 25};
        UI::Position const TIMER_POSITION = { 80, 435 };
        std::chrono::seconds const GAME_TIME(60);
        UI::AnimationSettings animationSettings;
        animationSettings.initialFallingHeight = BOARD_POSITION.y - GRID_SIZE;

        auto synchronizedTimer = std::make_shared<UI::SynchronizedAnimationTimer>();
        auto renderer = UI::SDLRendererFactory().createRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);
        auto backgroundSprite = std::make_shared<UI::SDLSprite>(renderer, "BackGround.jpg");
        auto gems = loadGems(renderer);
        auto selectionMarker = std::make_shared<UI::SDLSprite>(renderer, "Selected.png");
        auto grid = std::make_shared<UI::BoundedGrid>(BOARD_POSITION, GRID_SIZE, BOARD_WIDTH, BOARD_HEIGHT);
        auto animationsFactory = std::make_shared<UI::AnimationsFactory>(synchronizedTimer, animationSettings);
        auto boardAnimator = std::make_shared<UI::StagedBoardAnimator>(animationsFactory, animationsFactory, animationsFactory);
        auto board = std::make_shared<UI::AnimatedBoardView2>(gems, selectionMarker, grid, boardAnimator);
        auto timerLabel = std::make_shared<UI::SDLLabel>(renderer, FONT, FONT_SIZE, FONT_COLOR, TIMER_POSITION);
        auto background = std::make_shared<UI::Background>(backgroundSprite);
        UI::DrawFrameListeners uiElements = { background, boardAnimator, board, timerLabel };
        auto ui = std::make_shared<Candies::UI::SDLGameUI>(renderer, uiElements);
        auto itemGenerator = std::make_shared<Candies::Logic::StdItemGenerator>(gems.size());
        auto gameObserver = std::make_shared<BoardViewConnector>(board);
        auto gameLogic = Candies::Logic::GameFactory().createGame(itemGenerator, gameObserver);
        auto mouseItemSwapper = std::make_shared<Candies::UI::MouseItemSwapper>(board, gameLogic);
        auto timer = std::make_shared<Logic::ChronoTimer>(GAME_TIME);
        auto timeMonitor = std::make_shared<UI::TimeMonitor>(timer, timerLabel, mouseItemSwapper);
        UI::UpdateFrameListeners updateListeners = { timeMonitor, synchronizedTimer, boardAnimator };
        auto dispatcher = std::make_shared<Candies::UI::SDLEventDispatcher>(updateListeners, ui, mouseItemSwapper);
        auto runner = std::make_shared<Candies::GameRunner>(gameLogic, timer, dispatcher);
        return runner;
    }
}
