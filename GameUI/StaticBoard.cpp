#include "StaticBoard.hpp"

namespace Candies
{
    namespace UI
    {
        StaticBoard::StaticBoard(std::initializer_list<std::pair<const GameCore::ItemId, SpritePtr>> sprites, int gridSize, Position position)
        : sprites(sprites), gridSize(gridSize), position(position)
        {
        }

        void StaticBoard::addItem(GameCore::ItemId id, GameCore::Location loc)
        {
            items.push_back({sprites[id], loc});
        }

        void StaticBoard::update()
        {
            for (auto const& item : items)
                item.sprite->drawAt({int(item.location.x) * gridSize + position.x, int(item.location.y) * gridSize + position.y});
        }
    }
}
