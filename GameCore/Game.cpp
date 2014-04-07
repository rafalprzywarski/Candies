#include "Game.hpp"

namespace Candies
{
    namespace GameCore
    {
        Game::Game(ItemGeneratorPtr itemGenerator, unsigned boardWidth, unsigned boardHeight)
        : itemGenerator(std::move(itemGenerator)), board(boardWidth, boardHeight)
        {
        }
        
        void Game::start()
        {
            for (unsigned y = 0; y < board.getWidth(); ++y)
                for (unsigned x = 0; x < board.getHeight(); ++x)
                    board(x, y) = itemGenerator->generate();
        }
        
        Board Game::getBoard() const
        {
            return board;
        }
    }
}
