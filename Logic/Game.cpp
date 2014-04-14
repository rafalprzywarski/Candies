#include "Game.hpp"

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
                ColumnRange findMarkedRange(unsigned x) const
                {
                    ColumnRange range;
                    while (range.y < height && !isMarked({x, range.y}))
                        ++range.y;
                    while ((range.y + range.count) < height && isMarked({x, range.y + range.count}))
                        ++range.count;
                    return range;
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
                
                Mask findAlignedItems(Location loc1, Location loc2)
                {
                    markAlignedLocationsAlong<&Location::x>(loc2);
                    markAlignedLocationsAlong<&Location::x>(loc1);
                    markAlignedLocationsAlong<&Location::y>(loc2);
                    markAlignedLocationsAlong<&Location::y>(loc1);
                    return itemsToRemove;
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
                
                bool hasMovedItems() const { return !movedItems.empty(); }
                
                const Movements& getMovedItems() const { return movedItems; }
                
            private:
                Board board;
                ItemGeneratorPtr itemGenerator;
                Mask itemsToRemove;
                ItemIdsWithLocations addedItems;
                Movements movedItems;
               
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
                    auto markedRange = itemsToRemove.findMarkedRange(x);
                    if (markedRange.count == 0)
                        return 0;
                    for (unsigned y = markedRange.y; y > 0; --y)
                        moveItem({x, y - 1}, {x, y - 1 + markedRange.count});
                    return markedRange.count;
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
            observer->itemsAdded(initialBoard.getAddedItems());
            board = initialBoard.getBoard();
        }

        void Game::swapItems(Location loc1, Location loc2)
        {
            MutableBoard boardWithSwappedItems(board, itemGenerator);
            if (!boardWithSwappedItems.swapItems(loc1, loc2))
                return;
            
            boardWithSwappedItems.findAlignedItems(loc1, loc2);
            if (!boardWithSwappedItems.hasItemsToRemove())
                return;
            
            boardWithSwappedItems.removeItems();
            
            observer->itemsSwapped(loc1, loc2);
            observer->itemsRemoved(boardWithSwappedItems.getItemsToRemove());
            if (boardWithSwappedItems.hasMovedItems())
                observer->itemsMoved(boardWithSwappedItems.getMovedItems());
            observer->itemsAdded(boardWithSwappedItems.getAddedItems());
            board = boardWithSwappedItems.getBoard();
        }
        
        Board Game::getBoard() const
        {
            return board;
        }
    }
}
