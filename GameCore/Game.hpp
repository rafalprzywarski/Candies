#pragma once
#include "ItemGenerator.hpp"
#include "Board.hpp"

namespace Candies
{
    namespace GameCore
    {
        class Game
        {
        public:
            Game(ItemGeneratorPtr itemGenerator, unsigned boardWidth, unsigned boardHeight);
            void start();
            Board getBoard() const;
        private:
            ItemGeneratorPtr itemGenerator;
            Board board;
        };
    }
}
