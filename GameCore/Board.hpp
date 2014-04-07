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
                return items.at(x + y * width);
            }
            unsigned getWidth() const { return width; }
            unsigned getHeight() const { return height; }
        private:
            unsigned width, height;
            std::vector<ItemId> items;
        };
    }
}
