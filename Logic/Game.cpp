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

            Mask itemsToRemove = findAlignedItems(boardWithSwappedItems, loc1, loc2);
            if (itemsToRemove.isEmpty())
                return;
            
            board = boardWithSwappedItems;
            notifyObserver(loc1, loc2, itemsToRemove);
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
        
        void Game::notifyObserver(Location loc1, Location loc2, const Mask& itemsToRemove)
        {
            observer->itemsSwapped(loc1, loc2);
            itemsToRemove.forEachLocation([=](Location loc){ observer->itemRemoved(loc); });

            Mask itemsToAdd{board.getWidth(), board.getHeight()};
            for (unsigned x = 0; x < board.getWidth(); ++x)
            {
                unsigned firstRemoved = 0;
                while (firstRemoved < board.getHeight() && !itemsToRemove.isMarked({x, firstRemoved}))
                    ++firstRemoved;
                unsigned lastRemoved = firstRemoved;
                while (lastRemoved < board.getHeight() && itemsToRemove.isMarked({x, lastRemoved}))
                    ++lastRemoved;
                if (firstRemoved == board.getHeight())
                    continue;
                unsigned d = lastRemoved - firstRemoved;
                
                for (unsigned y = firstRemoved; y < lastRemoved; ++y)
                    itemsToAdd.mark({x, y - firstRemoved});
                for (unsigned y = firstRemoved; y > 0; --y)
                {
                    Location to{x, y - 1 + d}, from{x, y - 1};
                    board[to] = board[from];
                    observer->itemMoved(from, to);
                }
            }
            
            itemsToAdd.forEachLocation([=](Location loc){ addItemAt(loc); });
        }
        
        Game::Mask Game::findAlignedItems(const Board& boardWithSwappedItems, Location loc1, Location loc2)
        {
            Mask itemsToRemove{boardWithSwappedItems.getWidth(), boardWithSwappedItems.getHeight()};
            markAlignedLocationsAlong<&Location::x>(boardWithSwappedItems, loc2, itemsToRemove);
            markAlignedLocationsAlong<&Location::x>(boardWithSwappedItems, loc1, itemsToRemove);
            markAlignedLocationsAlong<&Location::y>(boardWithSwappedItems, loc2, itemsToRemove);
            markAlignedLocationsAlong<&Location::y>(boardWithSwappedItems, loc1, itemsToRemove);
            return std::move(itemsToRemove);
        }


        template <unsigned Location:: *Coord>
        void Game::markLocationsAlong(unsigned leftCount, unsigned rightCount, Location loc, Mask& mask)
        {
            loc.*Coord -= leftCount;
            for (int i = -int(leftCount); i <= int(rightCount); ++i, (loc.*Coord)++)
                mask.mark(loc);
        }

        template <unsigned Location:: *Coord>
        void Game::markAlignedLocationsAlong(const Board& boardWithSwappedItems, Location loc, Mask& mask)
        {
            auto leftAligned = boardWithSwappedItems.countAlignedInNegativeDirection<Coord>(loc, boardWithSwappedItems[loc]);
            auto rightAligned = boardWithSwappedItems.countAlignedInPositiveDirection<Coord>(loc, boardWithSwappedItems[loc]);
            
            if (!shouldSwap(leftAligned, rightAligned))
                return;

            markLocationsAlong<Coord>(leftAligned, rightAligned, loc, mask);
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
