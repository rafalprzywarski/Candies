#pragma once
#include <memory>
#include "Game.hpp"

namespace Candies
{
    namespace Logic
    {
        class GameFactory
        {
        public:
            GamePtr createGame(ItemGeneratorPtr itemGenerator, GameObserverPtr observer);
        };
    }
}
