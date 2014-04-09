#pragma once
#include "MouseEventListener.hpp"
#include "BoardView.hpp"
#include <GameCore/GameLogic.hpp>

namespace Candies
{
    namespace UI
    {
        class MouseItemSelector : public MouseEventListener
        {
        public:
            MouseItemSelector(BoardViewPtr board, GameCore::GameLogicPtr logic)
            : board(std::move(board)), logic(std::move(logic)) { }
            void mouseDown(int x, int y);
        private:
            BoardViewPtr board;
            GameCore::GameLogicPtr logic;
        };
    }
}
