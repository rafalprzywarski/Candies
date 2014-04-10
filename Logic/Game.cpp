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
            auto boardWithSwappedItems = board;
            boardWithSwappedItems.swapItems(loc1, loc2);

            auto signalSwap = [=]{ observer->itemsSwapped(loc1, loc2); };
            trySwapWithAlignmentAlong<&Location::x>(boardWithSwappedItems, loc1, loc2, signalSwap) ||
            trySwapWithAlignmentAlong<&Location::x>(boardWithSwappedItems, loc2, loc1, signalSwap) ||
            trySwapWithAlignmentAlong<&Location::y>(boardWithSwappedItems, loc1, loc2, signalSwap) ||
            trySwapWithAlignmentAlong<&Location::y>(boardWithSwappedItems, loc2, loc1, signalSwap);
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
        bool Game::trySwapWithAlignmentAlong(const Board& boardWithSwappedItems, Location loc1, Location loc2, F signalSwap)
        {
            auto leftAligned = boardWithSwappedItems.countAlignedInNegativeDirection<Coord>(loc2, board[loc1]);
            auto rightAligned = boardWithSwappedItems.countAlignedInPositiveDirection<Coord>(loc2, board[loc1]);
            
            if (!shouldSwap(leftAligned, rightAligned))
                return false;
            
            board = boardWithSwappedItems;
            signalSwap();
            removeItemsAlong<Coord>(leftAligned, rightAligned, loc2);
            addItemsAlong<Coord>(leftAligned, rightAligned, loc2);
            return true;
        }

        template <unsigned Location:: *Coord>
        void Game::removeItemsAlong(unsigned leftCount, unsigned rightCount, Location loc)
        {
            loc.*Coord -= leftCount;
            for (int i = -int(leftCount); i <= int(rightCount); ++i, (loc.*Coord)++)
                observer->itemRemoved(loc);
        }
        
        template <unsigned Location:: *Coord>
        void Game::addItemsAlong(unsigned leftCount, unsigned rightCount, Location loc)
        {
            loc.*Coord -= leftCount;
            for (int i = -int(leftCount); i <= int(rightCount); ++i, (loc.*Coord)++)
                addItemAt(loc);
        }

        bool Game::shouldSwap(unsigned count1, unsigned count2)
        {
            return count1 + count2 >= 2;
        }

        bool Game::areNeighbours(Location loc1, Location loc2)
        {
            return std::abs(int(loc1.y) - int(loc2.y)) + std::abs(int(loc1.x) - int(loc2.x)) == 1;
        }
    }
}
