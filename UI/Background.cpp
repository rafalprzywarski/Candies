#include "Background.hpp"

namespace Candies
{
    namespace UI
    {
        void Background::drawFrame() const
        {
            sprite->drawAt({0, 0});
        }
    }
}
