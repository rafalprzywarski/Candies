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
            : board(std::move(board)), logic(std::move(logic)), downPosition{0, 0}, enabled(true) { }
            void mouseDown(Position pos);
            void mouseUp(Position pos);
            void disable();
        private:
            BoardViewPtr board;
            Logic::GameLogicPtr logic;
            Position downPosition;
            bool enabled;
            
            void swapItemsAndClearSelection(const Logic::Locations& selected);
            bool selectAndSwap(Position position);
        };
    }
}
