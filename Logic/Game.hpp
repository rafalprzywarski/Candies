#pragma once
#include "ItemGenerator.hpp"
#include "Board.hpp"
#include "GameLogic.hpp"
#include "GameObserver.hpp"

namespace Candies
{
    namespace Logic
    {
        class Game : public GameLogic
        {
        public:
            Game(ItemGeneratorPtr itemGenerator, GameObserverPtr observer, unsigned boardWidth, unsigned boardHeight);
            void start();
            void swapItems(Location loc1, Location loc2);
            Board getBoard() const;
        private:
            
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
                template <typename F1>
                void forEachLocation(F1 f) const
                {
                    auto it = mask.begin();
                    for (unsigned y = 0; y < height; ++y)
                        for (unsigned x = 0; x < width; ++x)
                            if (*it++)
                                f({x, y});
                }
                ColumnRange findMarkedRange(unsigned x) const
                {
                    ColumnRange range;
                    while (range.y < height && !isMarked({x, range.y}))
                        ++range.y;
                    while (range.y < height && isMarked({x, range.y + range.count}))
                        ++range.count;
                    return range;
                }
            private:
                unsigned width, height;
                std::vector<bool> mask;
            };
            
            typedef std::vector<unsigned> Heights;

            ItemGeneratorPtr itemGenerator;
            GameObserverPtr observer;
            Board board;
            
            void addItemAt(Location loc);
            void applyChanges(const Board& boardWithSwappedItems, Location loc1, Location loc2, const Mask& itemsToRemove);
            void addItems(const Heights& itemsToAdd);
            unsigned moveItemsDown(unsigned x, const Mask& itemsToRemove);
            Heights moveItemsDown(const Mask& itemsToRemove);
            void moveItem(Location from, Location to);
            Mask findAlignedItems(const Board& boardWithSwappedItems, Location loc1, Location loc2);
            template <unsigned Location:: *Coord>
            void markLocationsAlong(unsigned leftCount, unsigned rightCount, Location loc, Mask& mask);
            template <unsigned Location:: *Coord>
            void markAlignedLocationsAlong(const Board& boardWithSwappedItems, Location loc, Mask& mask);
            bool shouldSwap(unsigned count1, unsigned count2);
            bool areNeighbours(Location loc1, Location loc2);
        };
        
        typedef std::shared_ptr<Game> GamePtr;
    }
}
