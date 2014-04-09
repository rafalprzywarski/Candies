#include "MouseItemSelector.hpp"

namespace Candies
{
    namespace UI
    {
        void MouseItemSelector::mouseDown(int x, int y)
        {
            board->selectItemAt({x, y});
        }
    }
}
