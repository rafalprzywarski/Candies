#pragma once
#include "ItemId.hpp"
#include <memory>

namespace Candies
{
    namespace GameCore
    {
        struct StubItemGenerator : ItemGenerator
        {
            ItemId generate() { return 0; }
        };
    }
}
