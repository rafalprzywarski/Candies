#pragma once
#include "Grid.hpp"

namespace Candies
{
    namespace UI
    {
        class InfiniteGrid : public Grid
        {
        public:
            InfiniteGrid(Position origin, int gridSize)
            : origin(origin), gridSize(gridSize) { }
            Position toPosition(Logic::Location loc);
            bool isValid(Position pos);
            Logic::Location toLocation(Position pos);
        private:
            Position origin;
            int gridSize;
        };

    }
}
