#include "AnimatedBoardView.hpp"
#include <algorithm>

namespace Candies
{
    namespace UI
    {
        AnimatedBoardView::AnimatedBoardView(Sprites sprites, SpritePtr selectionMarker, GridPtr grid, SpriteAnimatorPtr animator)
        : sprites(sprites.begin(), sprites.end()), selectionMarker(selectionMarker), grid(grid), animator(animator)
        {
        }

        void AnimatedBoardView::addItem(Logic::ItemId id, Logic::Location loc)
        {
            auto found = sprites.find(id);
            if (found == sprites.end())
                throw std::out_of_range("Invalid item id");
            items.insert({loc, found->second});
            animator->moveSprite(found->second, grid->toPosition(loc), grid->toPosition(loc));
        }

        void AnimatedBoardView::swapItems(Logic::Location loc1, Logic::Location loc2)
        {
            auto item1 = items.find(loc1), item2 = items.find(loc2);
            if (item1 == items.end() || item2 == items.end())
                return;
            animator->moveSprite(item1->second, grid->toPosition(loc1), grid->toPosition(loc2));
            animator->moveSprite(item2->second, grid->toPosition(loc2), grid->toPosition(loc1));
            std::swap(item1->second, item2->second);
        }

        void AnimatedBoardView::removeItem(Logic::Location loc)
        {
            auto it = items.find(loc);
            if (it == items.end())
                return;
            animator->destroySpriteAt(it->second, grid->toPosition(loc));
            items.erase(it);
        }

        void AnimatedBoardView::moveItem(Logic::Location from, Logic::Location to)
        {
            auto it = items.find(from);
            if (it == items.end())
                return;
            auto item = it->second;
            items.erase(it);
            items.insert({to, item});
            animator->moveSprite(item, grid->toPosition(from), grid->toPosition(to));
        }

        void AnimatedBoardView::drawFrame() const
        {
            animator->draw();
            for (auto const& itemLoc : selection)
                selectionMarker->drawAt(grid->toPosition(itemLoc));
        }
        
        void AnimatedBoardView::selectItemAt(Position pos)
        {
            if (!grid->isValid(pos))
                return;

            auto itemLoc = grid->toLocation(pos);
            if (itemExists(itemLoc) && !isItemAlreadySelected(itemLoc))
                selection.push_back(itemLoc);
        }

        Logic::Locations AnimatedBoardView::getSelectedItemLocations() const
        {
            return selection;
        }
        
        void AnimatedBoardView::clearSelection()
        {
            selection.clear();
        }

        bool AnimatedBoardView::itemExists(Logic::Location loc)
        {
            return items.count(loc) != 0;
        }
        
        bool AnimatedBoardView::isItemAlreadySelected(Logic::Location loc)
        {
            return std::find(selection.begin(), selection.end(), loc) != selection.end();
        }
    }
}
