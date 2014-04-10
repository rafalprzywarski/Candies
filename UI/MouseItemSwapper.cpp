#include "MouseItemSwapper.hpp"
#include <array>

namespace Candies
{
    namespace UI
    {
        void MouseItemSwapper::mouseDown(Position pos)
        {
            downPosition = pos;
        }
        
        void MouseItemSwapper::mouseUp(Position upPosition)
        {
            std::array<Position, 2> events{downPosition, upPosition};
            for (auto position : events)
                if (selectAndSwap(position))
                    return;
        }

        void MouseItemSwapper::swapItemsAndClearSelection(const Logic::Locations& selected)
        {
            logic->swapItems(selected[0], selected[1]);
            board->clearSelection();
        }
        
        bool MouseItemSwapper::selectAndSwap(Position position)
        {
            board->selectItemAt(position);
            auto selected = board->getSelectedItemLocations();
            if (selected.size() != 2u)
                return false;
            swapItemsAndClearSelection(selected);
            return true;
        }

    }
}
