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
            ItemGeneratorPtr itemGenerator;
            GameObserverPtr observer;
            Board board;
            
            void addItem(ItemId item, Location loc);
            template <unsigned Location:: *Coord>
            int countAlignedInNegativeDirection(Location loc, ItemId item);
            template <unsigned Location:: *Coord>
            int countAlignedInPositiveDirection(Location loc, ItemId item);
            template <unsigned Location:: *Coord, typename F>
            bool trySwapWithAlignmentAlong(Location loc1, Location loc2, F doSwap);
            template <unsigned Location:: *Coord>
            void removeItemsAlong(int leftCount, int rightCount, Location loc);
            template <unsigned Location:: *Coord>
            void addItemsAlong(int leftCount, int rightCount, Location loc);
            bool shouldSwap(int count1, int count2);
            bool areNeighbours(Location loc1, Location loc2);
        };
        
        typedef std::shared_ptr<Game> GamePtr;
    }
}
