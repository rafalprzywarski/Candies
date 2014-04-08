#include "StaticBoard.hpp"

namespace Candies
{
    namespace UI
    {
        StaticBoard::StaticBoard(std::vector<std::pair<const GameCore::ItemId, SpritePtr>> sprites, int gridSize, Position position)
        : sprites(sprites.begin(), sprites.end()), gridSize(gridSize), position(position)
        {
        }

        void StaticBoard::addItem(GameCore::ItemId id, GameCore::Location loc)
        {
            auto found = sprites.find(id);
            if (found == sprites.end())
                throw std::out_of_range("Invalid item id");
            items.push_back({found->second, loc});
        }

        void StaticBoard::update()
        {
            for (auto const& item : items)
                item.sprite->drawAt({int(item.location.x) * gridSize + position.x, int(item.location.y) * gridSize + position.y});
        }
    }
}
