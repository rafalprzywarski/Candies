#pragma once
#include "ItemId.hpp"
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
            
            ItemId& operator()(unsigned x, unsigned y)
            {
                return getItem<ItemId&>(items, x, y);
            }
            
            ItemId operator()(unsigned x, unsigned y) const
            {
                return getItem<ItemId>(items, x, y);
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
