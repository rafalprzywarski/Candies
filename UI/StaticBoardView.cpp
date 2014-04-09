#include "StaticBoardView.hpp"
#include <algorithm>

namespace Candies
{
    namespace UI
    {
        StaticBoardView::StaticBoardView(Sprites sprites, SpritePtr selectionMarker, int gridSize, Position origin)
        : sprites(sprites.begin(), sprites.end()), selectionMarker(selectionMarker), gridSize(gridSize), origin(origin)
        {
        }

        void StaticBoardView::addItem(Logic::ItemId id, Logic::Location loc)
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
            for (auto const& itemLoc : selection)
                selectionMarker->drawAt(toPosition(itemLoc));
        }
        
        void StaticBoardView::selectItemAt(Position pos)
        {
            if (pos.x < origin.x || pos.y < origin.y)
                return;

            auto itemLoc = toLocation(pos);
            if (itemExists(itemLoc) && !isItemAlreadySelected(itemLoc))
                selection.push_back(itemLoc);
        }

        Logic::Locations StaticBoardView::getSelectedItemLocations() const
        {
            return selection;
        }
        
        void StaticBoardView::clearSelection()
        {
            selection.clear();
        }

        Position StaticBoardView::toPosition(Logic::Location loc)
        {
            return {int(loc.x) * gridSize + origin.x, int(loc.y) * gridSize + origin.y};
        }

        Logic::Location StaticBoardView::toLocation(Position pos)
        {
            return {unsigned(pos.x - origin.x) / gridSize, unsigned(pos.y - origin.y) / gridSize};
        }

        bool StaticBoardView::itemExists(Logic::Location loc)
        {
            return items.count(loc) != 0;
        }
        
        bool StaticBoardView::isItemAlreadySelected(Logic::Location loc)
        {
            return std::find(selection.begin(), selection.end(), loc) != selection.end();
        }
    }
}
