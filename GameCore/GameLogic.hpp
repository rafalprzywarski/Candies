#pragma once
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
        };
        
        typedef std::shared_ptr<GameLogic> GameLogicPtr;
    }
}
