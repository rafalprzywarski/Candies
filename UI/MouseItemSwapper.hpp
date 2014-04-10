#pragma once
#include "MouseEventListener.hpp"
#include "BoardView.hpp"
#include <Logic/GameLogic.hpp>

namespace Candies
{
    namespace UI
    {
        class MouseItemSwapper : public MouseEventListener
        {
        public:
            MouseItemSwapper(BoardViewPtr board, Logic::GameLogicPtr logic)
            : board(std::move(board)), logic(std::move(logic)), downPosition{0, 0} { }
            void mouseDown(Position pos);
            void mouseUp(Position pos);
        private:
            BoardViewPtr board;
            Logic::GameLogicPtr logic;
            Position downPosition;
        };
    }
}
