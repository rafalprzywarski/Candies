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
            Position toPosition(Logic::Location loc) const;
            bool isValid(Position pos) const;
            Logic::Location toLocation(Position pos) const;
        private:
            Position origin;
            int gridSize;
        };

    }
}
