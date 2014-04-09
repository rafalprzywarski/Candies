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
            int countLeftAligned(Location loc, ItemId item);
            int countRightAligned(Location loc, ItemId item);
            template <typename F>
            bool trySwapWithHorizontalAlignment(Location loc1, Location loc2, F doSwap);
            void removeItemsHorizontally(int leftCount, int rightCount, Location loc);
            void addItemsHorizontally(int leftCount, int rightCount, Location loc);
            bool shouldSwap(int count1, int count2);
        };
        
        typedef std::shared_ptr<Game> GamePtr;
    }
}
