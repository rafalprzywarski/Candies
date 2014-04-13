#include "BoundedGrid.hpp"

namespace Candies
{
    namespace UI
    {
        Position BoundedGrid::toPosition(Logic::Location loc) const
        {
            return {int(loc.x) * gridSize + origin.x, int(loc.y) * gridSize + origin.y};
        }
        
        bool BoundedGrid::isValid(Position pos) const
        {
            return pos.x >= origin.x && pos.y >= origin.y && pos.x < (origin.x + size.x) && pos.y < (origin.y + size.y);
        }

        Logic::Location BoundedGrid::toLocation(Position pos) const
        {
            return {unsigned(pos.x - origin.x) / gridSize, unsigned(pos.y - origin.y) / gridSize};
        }
    }
}
