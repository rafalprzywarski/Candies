#include "MouseItemSelector.hpp"

namespace Candies
{
    namespace UI
    {
        void MouseItemSelector::mouseDown(Position pos)
        {
            board->selectItemAt(pos);
            auto selected = board->getSelectedItemLocations();
            if (selected.size() == 2u)
            {
                logic->swapItems(selected[0], selected[1]);
                board->clearSelection();
            }
        }
    }
}
