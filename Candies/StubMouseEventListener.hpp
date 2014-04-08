#pragma once
#include "ItemId.hpp"
#include <memory>
#include <iostream>

namespace Candies
{
    namespace UI
    {
        struct StubMouseEventListener : MouseEventListener
        {
            void mouseDown(int x, int y) { std::cerr << "mouse down at " << x << " " << y << std::endl; }
        };
    }
}
