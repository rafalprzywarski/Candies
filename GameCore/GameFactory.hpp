#pragma once
#include <memory>
#include "Game.hpp"

namespace Candies
{
    namespace GameCore
    {
        class GameFactory
        {
        public:
            GamePtr createGame(ItemGeneratorPtr itemGenerator);
        };
    }
}
