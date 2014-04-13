#include "InfiniteGrid.hpp"

namespace Candies
{
    namespace UI
    {
        Position InfiniteGrid::toPosition(Logic::Location loc) const
        {
            return {int(loc.x) * gridSize + origin.x, int(loc.y) * gridSize + origin.y};
        }
        
        bool InfiniteGrid::isValid(Position pos) const
        {
            return pos.x >= origin.x && pos.y >= origin.y;

        }

        Logic::Location InfiniteGrid::toLocation(Position pos) const
        {
            return {unsigned(pos.x - origin.x) / gridSize, unsigned(pos.y - origin.y) / gridSize};

        }
    }
}
