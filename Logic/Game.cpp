#include "Game.hpp"

namespace Candies
{
    namespace Logic
    {
        Game::Game(ItemGeneratorPtr itemGenerator, GameObserverPtr observer, unsigned boardWidth, unsigned boardHeight)
        : itemGenerator(std::move(itemGenerator)), observer(observer), board(boardWidth, boardHeight)
        {
        }
        
        void Game::start()
        {
            for (unsigned y = 0; y < board.getWidth(); ++y)
            {
                for (unsigned x = 0; x < board.getHeight(); ++x)
                {
                    auto item = itemGenerator->generate();
                    board[{x, y}] = item;
                    observer->itemAdded(item, {x, y});
                }
            }
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
