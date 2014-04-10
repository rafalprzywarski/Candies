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
            class Mask
            {
            public:
                Mask(unsigned width, unsigned height)
                : width(width), height(height), mask(width * height, false) { }
                void mark(Location loc)
                {
                    mask[loc.x + loc.y * width] = true;
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
            private:
                unsigned width, height;
                std::vector<bool> mask;
            };

            ItemGeneratorPtr itemGenerator;
            GameObserverPtr observer;
            Board board;
            
            void addItemAt(Location loc);
            void notifyObserver(Location loc1, Location loc2, const Mask& itemsToRemove);
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
