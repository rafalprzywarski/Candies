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
            auto leftAligned = countLeftAligned(loc1, board[loc2]);
            auto rightAligned = countRightAligned(loc1, board[loc2]);
            
            if (leftAligned + rightAligned >= 2)
            {
                observer->itemsSwapped(loc1, loc2);
                for (int i = -leftAligned; i <= rightAligned; ++i)
                    observer->itemRemoved({unsigned(int(loc1.x) + i), loc1.y});
                for (int i = -leftAligned; i <= rightAligned; ++i)
                    observer->itemAdded(itemGenerator->generate(), {unsigned(int(loc1.x) + i), loc1.y});
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
        
        int Game::countLeftAligned(Location loc, ItemId item)
        {
            int count = 0;
            loc.x--;
            while (board[loc] == item)
            {
                loc.x--;
                count++;
            }
            return count;
        }
        
        int Game::countRightAligned(Location loc, ItemId item)
        {
            int count = 0;
            loc.x++;
            while (board[loc] == item)
            {
                loc.x++;
                count++;
            }
            return count;
        }
    }
}
