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
            auto doSwap = [=]{ observer->itemsSwapped(loc1, loc2); };
            trySwapWithHorizontalAlignment(loc1, loc2, doSwap) ||
            trySwapWithHorizontalAlignment(loc2, loc1, doSwap);
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

            while (loc.x > 0)
            {
                if (board[{loc.x - 1, loc.y}] != item)
                    return count;
                count++;
                loc.x--;
            }
            return count;
        }
        
        int Game::countRightAligned(Location loc, ItemId item)
        {
            int count = 0;
            
            while ((loc.x + 1) < board.getWidth())
            {
                if (board[{loc.x + 1, loc.y}] != item)
                    return count;
                count++;
                loc.x++;
            }
            return count;
        }
    
        template <typename F>
        bool Game::trySwapWithHorizontalAlignment(Location loc1, Location loc2, F doSwap)
        {
            auto leftAligned = countLeftAligned(loc1, board[loc2]);
            auto rightAligned = countRightAligned(loc1, board[loc2]);
            
            if (!shouldSwap(leftAligned, rightAligned))
                return false;
            
            doSwap();
            removeItemsHorizontally(leftAligned, rightAligned, loc1);
            addItemsHorizontally(leftAligned, rightAligned, loc1);
            return true;
        }

        void Game::removeItemsHorizontally(int leftCount, int rightCount, Location loc)
        {
            for (int i = -leftCount; i <= rightCount; ++i)
                observer->itemRemoved({unsigned(int(loc.x) + i), loc.y});
        }
        
        void Game::addItemsHorizontally(int leftCount, int rightCount, Location loc)
        {
            for (int i = -leftCount; i <= rightCount; ++i)
                observer->itemAdded(itemGenerator->generate(), {unsigned(int(loc.x) + i), loc.y});
        }

        bool Game::shouldSwap(int count1, int count2)
        {
            return count1 + count2 >= 2;
        }

    }
}
