#pragma once
#include "MouseEventListener.hpp"
#include "BoardView.hpp"

namespace Candies
{
    namespace UI
    {
        class MouseItemSelector : public MouseEventListener
        {
        public:
            MouseItemSelector(BoardViewPtr board) : board(std::move(board)) { }
            void mouseDown(int x, int y);
        private:
            BoardViewPtr board;
        };
    }
}
