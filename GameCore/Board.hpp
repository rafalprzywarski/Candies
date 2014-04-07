#pragma once
#include "ItemId.hpp"
#include "Location.hpp"
#include <vector>

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
    }
}
