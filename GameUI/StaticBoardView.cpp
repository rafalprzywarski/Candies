#include "StaticBoardView.hpp"

namespace Candies
{
    namespace UI
    {
        StaticBoardView::StaticBoardView(std::vector<std::pair<const GameCore::ItemId, SpritePtr>> sprites, int gridSize, Position origin)
        : sprites(sprites.begin(), sprites.end()), gridSize(gridSize), origin(origin)
        {
        }

        void StaticBoardView::addItem(GameCore::ItemId id, GameCore::Location loc)
        {
            auto found = sprites.find(id);
            if (found == sprites.end())
                throw std::out_of_range("Invalid item id");
            items.push_back({found->second, loc});
        }

        void StaticBoardView::update()
        {
            for (auto const& item : items)
                item.sprite->drawAt({int(item.location.x) * gridSize + origin.x, int(item.location.y) * gridSize + origin.y});
        }
        
        void StaticBoardView::selectItemAt(Position pos)
        {
            if (items.empty())
                return;
            selection.push_back({unsigned(pos.x - origin.x) / gridSize, unsigned(pos.y - origin.y) / gridSize});
        }

        GameCore::Locations StaticBoardView::getSelectedItemLocations() const
        {
            return selection;
        }

    }
}
