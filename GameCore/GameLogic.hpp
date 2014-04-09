#pragma once
#include "Location.hpp"
#include <memory>

namespace Candies
{
    namespace GameCore
    {
        class GameLogic
        {
        public:
            virtual ~GameLogic() { }
            virtual void start() = 0;
            virtual void swapItems(Location loc1, Location loc2) = 0;
        };
        
        typedef std::shared_ptr<GameLogic> GameLogicPtr;
    }
}
