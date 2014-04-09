#include "GameFactory.hpp"

namespace Candies
{
    namespace Logic
    {
        GamePtr GameFactory::createGame(ItemGeneratorPtr itemGenerator, GameObserverPtr observer)
        {
            unsigned BOARD_WIDTH = 8, BOARD_HEIGHT = 8;
            return std::make_shared<Game>(itemGenerator, observer, BOARD_WIDTH, BOARD_HEIGHT);
        }
    }

}
