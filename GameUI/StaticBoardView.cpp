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
            items.insert({loc, found->second});
        }

        void StaticBoardView::update()
        {
            for (auto const& item : items)
                item.second->drawAt(toPosition(item.first));
        }
        
        void StaticBoardView::selectItemAt(Position pos)
        {
            if (pos.x < origin.x || pos.y < origin.y)
                return;

            auto itemLoc = toLocation(pos);
            if (items.count(itemLoc))
                selection.push_back(itemLoc);
        }

        GameCore::Locations StaticBoardView::getSelectedItemLocations() const
        {
            return selection;
        }

        Position StaticBoardView::toPosition(GameCore::Location loc)
        {
            return {int(loc.x) * gridSize + origin.x, int(loc.y) * gridSize + origin.y};
        }

        GameCore::Location StaticBoardView::toLocation(Position pos)
        {
            return {unsigned(pos.x - origin.x) / gridSize, unsigned(pos.y - origin.y) / gridSize};
        }

    }
}
