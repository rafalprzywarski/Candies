#pragma once
#include "ItemId.hpp"
#include "Location.hpp"
#include <vector>
#include <ostream>

namespace Candies
{
    namespace Logic
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
            
            template <unsigned Location:: *Coord>
            unsigned countAlignedInNegativeDirection(Location loc, ItemId item)
            {
                unsigned count = 0;
                
                while (loc.*Coord != 0)
                {
                    (loc.*Coord)--;
                    if ((*this)[loc] != item)
                        return count;
                    count++;
                }
                return count;
            }
            
            template <unsigned Location:: *Coord>
            unsigned countAlignedInPositiveDirection(Location loc, ItemId item)
            {
                unsigned count = 0;
                
                while ((loc.*Coord + 1) != getSize().*Coord)
                {
                    (loc.*Coord)++;
                    if ((*this)[loc] != item)
                        return count;
                    count++;
                }
                return count;
            }
            
            void swapItems(Location loc1, Location loc2)
            {
                std::swap((*this)[loc1], (*this)[loc2]);
            }
            
        private:
            unsigned width, height;
            std::vector<ItemId> items;
            
            template <typename As, typename Container>
            As getItem(Container& c, unsigned x, unsigned y) const
            {
                if (x >= width || y >= height)
                    throw std::out_of_range("Board access out of bounds");
                return c.at(x + y * width);
            }
            
            Location getSize() const
            {
                return {getWidth(), getHeight()};
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
