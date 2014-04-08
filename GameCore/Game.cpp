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
                    board[{x, y}] = itemGenerator->generate();
        }

        void Game::swapItems(Location loc1, Location loc2)
        {
            if (board[loc2] == board[{loc1.x - 1, loc1.y}])
                std::swap(board[loc1], board[loc2]);
        }
        
        Board Game::getBoard() const
        {
            return board;
        }
    }
}
