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
                    addItemAt({x, y});
        }

        void Game::swapItems(Location loc1, Location loc2)
        {
            if (!areNeighbours(loc1, loc2))
                return;
            auto signalSwap = [=]{ observer->itemsSwapped(loc1, loc2); };
            trySwapWithAlignmentAlong<&Location::x>(loc1, loc2, signalSwap) ||
            trySwapWithAlignmentAlong<&Location::x>(loc2, loc1, signalSwap) ||
            trySwapWithAlignmentAlong<&Location::y>(loc1, loc2, signalSwap) ||
            trySwapWithAlignmentAlong<&Location::y>(loc2, loc1, signalSwap);
        }
        
        Board Game::getBoard() const
        {
            return board;
        }
        
        void Game::addItemAt(Location loc)
        {
            auto item = itemGenerator->generate();
            board[loc] = item;
            observer->itemAdded(item, loc);
        }
        
        template <unsigned Location:: *Coord, typename F>
        bool Game::trySwapWithAlignmentAlong(Location loc1, Location loc2, F signalSwap)
        {
            auto leftAligned = board.countAlignedInNegativeDirection<Coord>(loc1, board[loc2]);
            auto rightAligned = board.countAlignedInPositiveDirection<Coord>(loc1, board[loc2]);
            
            if (!shouldSwap(leftAligned, rightAligned))
                return false;
            
            board[loc2] = board[loc1];
            signalSwap();
            removeItemsAlong<Coord>(leftAligned, rightAligned, loc1);
            addItemsAlong<Coord>(leftAligned, rightAligned, loc1);
            return true;
        }

        template <unsigned Location:: *Coord>
        void Game::removeItemsAlong(int leftCount, int rightCount, Location loc)
        {
            loc.*Coord -= unsigned(leftCount);
            for (int i = -leftCount; i <= rightCount; ++i, (loc.*Coord)++)
                observer->itemRemoved(loc);
        }
        
        template <unsigned Location:: *Coord>
        void Game::addItemsAlong(int leftCount, int rightCount, Location loc)
        {
            loc.*Coord -= unsigned(leftCount);
            for (int i = -leftCount; i <= rightCount; ++i, (loc.*Coord)++)
                addItemAt(loc);
        }

        bool Game::shouldSwap(int count1, int count2)
        {
            return count1 + count2 >= 2;
        }

        bool Game::areNeighbours(Location loc1, Location loc2)
        {
            return std::abs(int(loc1.y) - int(loc2.y)) + std::abs(int(loc1.x) - int(loc2.x)) == 1;
        }
    }
}
