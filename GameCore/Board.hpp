#pragma once
#include "ItemId.hpp"
#include "Location.hpp"
#include <vector>
#include <ostream>

namespace Candies
{
    namespace GameCore
    {
        class Board
        {
        public:
            Board(unsigned width, unsigned height)
            : width(width), height(height), items(width * height) { }
            
            ItemId& operator[](Location loc)
            {
                return getItem<ItemId&>(items, loc.x, loc.y);
            }
            
            ItemId operator[](Location loc) const
            {
                return getItem<ItemId>(items, loc.x, loc.y);
            }
            
            unsigned getWidth() const { return width; }
            unsigned getHeight() const { return height; }
            
        private:
            unsigned width, height;
            std::vector<ItemId> items;
            
            template <typename As, typename Container>
            As getItem(Container& c, unsigned x, unsigned y) const
            {
                return c.at(x + y * width);
            }
        };
        
        inline bool operator==(const Board& left, const Board& right)
        {
            if (left.getWidth() != right.getWidth() || left.getHeight() != right.getHeight())
                return false;
            for (unsigned y = 0; y < left.getHeight(); ++y)
                for (unsigned x = 0; x < left.getWidth(); ++x)
                    if (left[{x, y}] != right[{x, y}])
                        return false;
            return true;
        }
        
        inline std::ostream& operator<<(std::ostream& os, const Board& board)
        {
            os << "Board " << board.getWidth() << "x" << board.getHeight() << " [ ";
            for (unsigned y = 0; y < board.getHeight(); ++y)
            {
                os << "[ ";
                for (unsigned x = 0; x < board.getWidth(); ++x)
                    os << board[{x, y}] << " ";
                os << "] ";
            }
            return os << "]";
        }
    }
}
