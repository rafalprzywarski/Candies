#include "Game.hpp"

namespace Candies
{
    namespace Logic
    {
        Game::Game(ItemGeneratorPtr itemGenerator, GameObserverPtr observer, unsigned boardWidth, unsigned boardHeight)
        : itemGenerator(std::move(itemGenerator)), observer(observer), board(boardWidth, boardHeight)
        {
        }
        
        void Game::start()
        {
            for (unsigned y = 0; y < board.getWidth(); ++y)
                for (unsigned x = 0; x < board.getHeight(); ++x)
                    addItem(itemGenerator->generate(), {x, y});
        }

        void Game::swapItems(Location loc1, Location loc2)
        {
            if (board[loc2] == board[{loc1.x - 1, loc1.y}] && board[loc2] == board[{loc1.x - 2, loc1.y}])
            {
                observer->itemsSwapped(loc1, loc2);
                observer->itemRemoved({loc1.x - 2, loc1.y});
                observer->itemRemoved({loc1.x - 1, loc1.y});
                observer->itemRemoved(loc1);
                addItem(itemGenerator->generate(), {loc1.x - 2, loc1.y});
                addItem(itemGenerator->generate(), {loc1.x - 1, loc1.y});
                addItem(itemGenerator->generate(), loc1);
            }
            else if (board[loc2] == board[{loc1.x + 1, loc1.y}] && board[loc2] == board[{loc1.x + 2, loc1.y}])
            {
                observer->itemsSwapped(loc1, loc2);
                observer->itemRemoved({loc1.x + 2, loc1.y});
                observer->itemRemoved({loc1.x + 1, loc1.y});
                observer->itemRemoved(loc1);
                addItem(itemGenerator->generate(), loc1);
                addItem(itemGenerator->generate(), {loc1.x + 1, loc1.y});
                addItem(itemGenerator->generate(), {loc1.x + 2, loc1.y});
            }
            else if (board[loc2] == board[{loc1.x + 1, loc1.y}] && board[loc2] == board[{loc1.x - 1, loc1.y}])
            {
                observer->itemsSwapped(loc1, loc2);
                observer->itemRemoved({loc1.x - 1, loc1.y});
                observer->itemRemoved({loc1.x + 1, loc1.y});
                observer->itemRemoved(loc1);
                addItem(itemGenerator->generate(), {loc1.x - 1, loc1.y});
                addItem(itemGenerator->generate(), loc1);
                addItem(itemGenerator->generate(), {loc1.x + 1, loc1.y});
            }
        }
        
        Board Game::getBoard() const
        {
            return board;
        }
        
        void Game::addItem(ItemId item, Location loc)
        {
            board[loc] = item;
            observer->itemAdded(item, loc);
        }

    }
}
