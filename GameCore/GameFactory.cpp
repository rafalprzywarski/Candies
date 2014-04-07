#include "GameFactory.hpp"

namespace Candies
{
    namespace GameCore
    {
        std::shared_ptr<Game> GameFactory::createGame(ItemGeneratorPtr itemGenerator)
        {
            return std::make_shared<Game>(itemGenerator, 8, 8);
        }
    }

}
