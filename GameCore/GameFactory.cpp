#include "GameFactory.hpp"

namespace Candies
{
    namespace GameCore
    {
        GamePtr GameFactory::createGame(ItemGeneratorPtr itemGenerator)
        {
            unsigned BOARD_WIDTH = 8, BOARD_HEIGHT = 8;
            return std::make_shared<Game>(itemGenerator, BOARD_WIDTH, BOARD_HEIGHT);
        }
    }

}
