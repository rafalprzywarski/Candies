#pragma once
#include "ItemGenerator.hpp"
#include "Board.hpp"
#include "Location.hpp"
#include "GameLogic.hpp"

namespace Candies
{
    namespace GameCore
    {
        class Game : public GameLogic
        {
        public:
            Game(ItemGeneratorPtr itemGenerator, unsigned boardWidth, unsigned boardHeight);
            void start();
            void swapItems(Location loc1, Location loc2);
            Board getBoard() const;
        private:
            ItemGeneratorPtr itemGenerator;
            Board board;
        };
        
        typedef std::shared_ptr<Game> GamePtr;
    }
}
