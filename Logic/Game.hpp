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
            
            void notifyObserver(const Locations& removed, const Movements& moved, const ItemIdsWithLocations& added);

            template <typename MutableBoard>
            void removeAllAlignedItems(MutableBoard& trialBoard);
        };
        
        typedef std::shared_ptr<Game> GamePtr;
    }
}
