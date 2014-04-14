#include "Game.hpp"
#include <iostream>

namespace Candies
{
    namespace Logic
    {
        namespace
        {
            struct ColumnRange
            {
                unsigned y{}, count{};
            };
            
            class Mask
            {
            public:
                Mask(unsigned width, unsigned height)
                : width(width), height(height), mask(width * height, false) { }
                void mark(Location loc)
                {
                    mask.at(loc.x + loc.y * width) = true;
                }
                bool isMarked(Location loc) const
                {
                    return mask.at(loc.x + loc.y * width);
                }
                bool isEmpty() const
                {
                    return std::count(mask.begin(), mask.end(), true) == 0;
                }
                Locations getLocations() const
                {
                    Locations locs;
                    auto it = mask.begin();
                    for (unsigned y = 0; y < height; ++y)
                        for (unsigned x = 0; x < width; ++x)
                            if (*it++)
                                locs.emplace_back(x, y);
                    return locs;
                }
            private:
                unsigned width, height;
                std::vector<bool> mask;
            };
            
            typedef std::vector<unsigned> Heights;

            class MutableBoard
            {
            public:
                MutableBoard(const Board& board, ItemGeneratorPtr itemGenerator)
                : board(board), itemGenerator(itemGenerator), itemsToRemove{board.getWidth(), board.getHeight()}
                {
                }
                
                bool swapItems(Location loc1, Location loc2)
                {
                    if (!areNeighbours(loc1, loc2))
                        return false;
                    this->board.swapItems(loc1, loc2);
                    return true;
                }
                
                void fillWithItems()
                {
                    for (unsigned y = 0; y < board.getWidth(); ++y)
                        for (unsigned x = 0; x < board.getHeight(); ++x)
                            addItemAt({x, y});
                }
                
                void findAlignedItems(Location loc1, Location loc2)
                {
                    markAlignedLocations(loc1);
                    markAlignedLocations(loc2);
                }
                
                void findAlignedItems(const ItemIdsWithLocations& locs)
                {
                    for (auto& loc : locs)
                        markAlignedLocations(loc.location);
                }
                
                void findAlignedItems(const Movements& movs)
                {
                    for (auto& m : movs)
                        markAlignedLocations(m.to);
                }
                
                bool hasItemsToRemove() const
                {
                    return !itemsToRemove.isEmpty();
                }
                
                void removeItems()
                {
                    auto itemsToAdd = moveItemsDown();
                    addItems(itemsToAdd);
                }

                Board getBoard() const { return board; }
        
                const ItemIdsWithLocations& getAddedItems() const { return addedItems; }
                
                Locations getItemsToRemove() const { return itemsToRemove.getLocations(); }
                
                const Movements& getMovedItems() const { return movedItems; }
                
            private:
                Board board;
                ItemGeneratorPtr itemGenerator;
                Mask itemsToRemove;
                ItemIdsWithLocations addedItems;
                Movements movedItems;
               
                void markAlignedLocations(Location loc)
                {
                    markAlignedLocationsAlong<&Location::x>(loc);
                    markAlignedLocationsAlong<&Location::y>(loc);
                }
                
                template <unsigned Location:: *Coord>
                void markAlignedLocationsAlong(Location loc)
                {
                    auto leftAligned = board.countAlignedInNegativeDirection<Coord>(loc, board[loc]);
                    auto rightAligned = board.countAlignedInPositiveDirection<Coord>(loc, board[loc]);
                    
                    if (!shouldSwap(leftAligned, rightAligned))
                        return;
                    
                    markLocationsAlong<Coord>(leftAligned, rightAligned, loc);
                }
                
                template <unsigned Location:: *Coord>
                void markLocationsAlong(unsigned leftCount, unsigned rightCount, Location loc)
                {
                    loc.*Coord -= leftCount;
                    for (int i = -int(leftCount); i <= int(rightCount); ++i, (loc.*Coord)++)
                        itemsToRemove.mark(loc);
                }
                
                bool shouldSwap(unsigned count1, unsigned count2)
                {
                    return count1 + count2 >= 2;
                }
                
                void addItemAt(Location loc)
                {
                    auto item = itemGenerator->generate();
                    board[loc] = item;
                    addedItems.emplace_back(item, loc);
                }
                
                void addItems(const Heights& itemsToAdd)
                {
                    ItemIdsWithLocations addedItems;
                    for (unsigned x = 0; x < board.getWidth(); ++x)
                        for (unsigned y = 0; y < itemsToAdd[x]; ++y)
                            addItemAt({x, y});
                }
                
                
                Heights moveItemsDown()
                {
                    Heights itemsToAdd(board.getWidth(), 0);
                    for (unsigned x = 0; x < board.getWidth(); ++x)
                        itemsToAdd[x] = moveItemsDown(x);
                    return std::move(itemsToAdd);
                }
                
                unsigned moveItemsDown(unsigned x)
                {
                    unsigned dy = board.getHeight();
                    for (unsigned sy = board.getHeight(); sy > 0; --sy)
                    {
                        if (!itemsToRemove.isMarked({x, sy - 1}))
                        {
                            if (dy != sy)
                                moveItem({x, sy - 1}, {x, dy - 1});
                            --dy;
                        }
                    }
                    return dy;
                }

                void moveItem(Location from, Location to)
                {
                    board[to] = board[from];
                    movedItems.emplace_back(from, to);
                }
                
                static bool areNeighbours(Location loc1, Location loc2)
                {
                    return std::abs(int(loc1.y) - int(loc2.y)) + std::abs(int(loc1.x) - int(loc2.x)) == 1;
                }
            };
        }
        
        Game::Game(ItemGeneratorPtr itemGenerator, GameObserverPtr observer, unsigned boardWidth, unsigned boardHeight)
        : itemGenerator(std::move(itemGenerator)), observer(observer), board(boardWidth, boardHeight)
        {
        }
        
        void Game::start()
        {
            MutableBoard initialBoard(board, itemGenerator);
            initialBoard.fillWithItems();
            auto addedItems = initialBoard.getAddedItems();
            observer->itemsAdded(addedItems);
            board = initialBoard.getBoard();
            MutableBoard trialBoard(board, itemGenerator);
            trialBoard.findAlignedItems(addedItems);
            removeAllAlignedItems(trialBoard);
        }

        void Game::swapItems(Location loc1, Location loc2)
        {
            MutableBoard trialBoard(board, itemGenerator);
            if (!trialBoard.swapItems(loc1, loc2))
            {
                observer->itemsNotSwapped(loc1, loc2);
                return;
            }
            
            trialBoard.findAlignedItems(loc1, loc2);
            if (!trialBoard.hasItemsToRemove())
            {
                observer->itemsNotSwapped(loc1, loc2);
                return;
            }

            observer->itemsSwapped(loc1, loc2);
            
            removeAllAlignedItems(trialBoard);
        }
        
        template <typename MutableBoard>
        void Game::removeAllAlignedItems(MutableBoard& trialBoard)
        {
            while (trialBoard.hasItemsToRemove())
            {
                trialBoard.removeItems();
                
                auto addedItems = trialBoard.getAddedItems();
                auto movedItems = trialBoard.getMovedItems();
                
                notifyObserver(trialBoard.getItemsToRemove(), movedItems, addedItems);
                
                board = trialBoard.getBoard();
                trialBoard = MutableBoard(board, itemGenerator);
                trialBoard.findAlignedItems(addedItems);
                trialBoard.findAlignedItems(movedItems);
            }
        }
        
        Board Game::getBoard() const
        {
            return board;
        }
        
        void Game::notifyObserver(const Locations& removed, const Movements& moved, const ItemIdsWithLocations& added)
        {
            observer->itemsRemoved(removed);
            if (!moved.empty())
                observer->itemsMoved(moved);
            observer->itemsAdded(added);
        }
    }
}
