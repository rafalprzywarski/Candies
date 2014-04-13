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
            //TODO: expose hidden classes
            if (!areNeighbours(loc1, loc2))
                return;
            auto boardWithSwappedItems = board;
            boardWithSwappedItems.swapItems(loc1, loc2);

            Mask itemsToRemove = findAlignedItems(boardWithSwappedItems, loc1, loc2);
            if (itemsToRemove.isEmpty())
                return;
            
            applyChanges(boardWithSwappedItems, loc1, loc2, itemsToRemove);
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
        
        void Game::applyChanges(const Board& boardWithSwappedItems, Location loc1, Location loc2, const Mask& itemsToRemove)
        {
            board = boardWithSwappedItems;
            observer->itemsSwapped(loc1, loc2);
            observer->itemsRemoved(itemsToRemove.getLocations());
            Movements movedItems;
            auto itemsToAdd = moveItemsDown(itemsToRemove, movedItems);
            if (!movedItems.empty())
                observer->itemsMoved(movedItems);
            addItems(itemsToAdd);
        }
        
        void Game::addItems(const Heights& itemsToAdd)
        {
            for (unsigned x = 0; x < board.getWidth(); ++x)
                for (unsigned y = 0; y < itemsToAdd[x]; ++y)
                    addItemAt({x, y});
        }
        
        Game::Heights Game::moveItemsDown(const Mask& itemsToRemove, Movements& movedItems)
        {
            Heights itemsToAdd(board.getWidth(), 0);
            for (unsigned x = 0; x < board.getWidth(); ++x)
                itemsToAdd[x] = moveItemsDown(x, itemsToRemove, movedItems);
            return std::move(itemsToAdd);
        }

        unsigned Game::moveItemsDown(unsigned x, const Mask& itemsToRemove, Movements& movedItems)
        {
            auto markedRange = itemsToRemove.findMarkedRange(x);
            if (markedRange.count == 0)
                return 0;
            for (unsigned y = markedRange.y; y > 0; --y)
                moveItem({x, y - 1}, {x, y - 1 + markedRange.count}, movedItems);
            return markedRange.count;
        }
        
        void Game::moveItem(Location from, Location to, Movements& movedItems)
        {
            board[to] = board[from];
            movedItems.emplace_back(from, to);
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
