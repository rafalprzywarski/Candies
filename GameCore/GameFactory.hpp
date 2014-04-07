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
            std::shared_ptr<Game> createGame(ItemGeneratorPtr itemGenerator);
        };
    }
}
