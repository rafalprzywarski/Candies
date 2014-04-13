#include "StaticBoardView.hpp"
#include <algorithm>

namespace Candies
{
    namespace UI
    {
        StaticBoardView::StaticBoardView(Sprites sprites, SpritePtr selectionMarker, GridPtr grid)
        : sprites(sprites.begin(), sprites.end()), selectionMarker(selectionMarker), grid(grid)
        {
        }

        void StaticBoardView::addItem(Logic::ItemId id, Logic::Location loc)
        {
            auto found = sprites.find(id);
            if (found == sprites.end())
                throw std::out_of_range("Invalid item id");
            items.insert({loc, found->second});
        }

        void StaticBoardView::swapItems(Logic::Location loc1, Logic::Location loc2)
        {
            auto item1 = items.find(loc1), item2 = items.find(loc2);
            if (item1 == items.end() || item2 == items.end())
                return;
            std::swap(item1->second, item2->second);
        }

        void StaticBoardView::removeItem(Logic::Location loc)
        {
            items.erase(loc);
        }

        void StaticBoardView::moveItem(Logic::Location from, Logic::Location to)
        {
            auto it = items.find(from);
            if (it == items.end())
                return;
            auto item = it->second;
            items.erase(it);
            items.insert({to, item});
        }

        void StaticBoardView::update()
        {
            for (auto const& item : items)
                item.second->drawAt(grid->toPosition(item.first));
            for (auto const& itemLoc : selection)
                selectionMarker->drawAt(grid->toPosition(itemLoc));
        }
        
        void StaticBoardView::selectItemAt(Position pos)
        {
            if (!grid->isValid(pos))
                return;

            auto itemLoc = grid->toLocation(pos);
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
