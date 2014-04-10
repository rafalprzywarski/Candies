#include "MouseItemSwapper.hpp"

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
            board->selectItemAt(downPosition);
            board->selectItemAt(upPosition);
            auto selected = board->getSelectedItemLocations();
            if (selected.size() == 2u)
            {
                logic->swapItems(selected[0], selected[1]);
                board->clearSelection();
            }
        }
    }
}
