#pragma once
#include "Grid.hpp"

namespace Candies
{
    namespace UI
    {
        class BoundedGrid : public Grid
        {
        public:
            BoundedGrid(Position origin, int gridSize, int width, int height)
            : origin(origin), size(width * gridSize, height * gridSize), gridSize(gridSize) { }
            Position toPosition(Logic::Location loc) const;
            bool isValid(Position pos) const;
            Logic::Location toLocation(Position pos) const;
        private:
            Position origin, size;
            int gridSize;
        };

    }
}
