#include "AnimatedBoardView.hpp"
#include <algorithm>

namespace Candies
{
    namespace UI
    {
        AnimatedBoardView::AnimatedBoardView(Sprites sprites, SpritePtr selectionMarker, GridPtr grid, BoardAnimatorPtr animator)
        : sprites(sprites.begin(), sprites.end()), selectionMarker(selectionMarker), grid(grid), animator(animator)
        {
        }

        void AnimatedBoardView::addItems(const Logic::ItemIdsWithLocations& items)
        {
            SpritesWithPositions itemSprites;
            for (auto& item : items)
            {
                auto found = sprites.find(item.item);
                if (found == sprites.end())
                    throw std::out_of_range("Invalid item id");
                itemSprites.emplace_back(found->second, grid->toPosition(item.location));
            }
            animator->addFallingAnimation(itemSprites);
        }

        void AnimatedBoardView::swapItems(Logic::Location loc1, Logic::Location loc2)
        {
            animator->addSwappingAnimation(grid->toPosition(loc1), grid->toPosition(loc2));
        }

        void AnimatedBoardView::dontSwapItems(Logic::Location loc1, Logic::Location loc2)
        {
            animator->addSwappingAnimation(grid->toPosition(loc1), grid->toPosition(loc2));
            animator->addSwappingAnimation(grid->toPosition(loc2), grid->toPosition(loc1));
        }

        void AnimatedBoardView::removeItems(const Logic::Locations& locs)
        {
            Positions positions;
            positions.reserve(locs.size());
            std::transform(locs.begin(), locs.end(), std::back_inserter(positions), [=](Logic::Location l) { return grid->toPosition(l); });
            animator->addDisappearingAnimation(positions);
        }

        void AnimatedBoardView::moveItems(const Logic::Movements& movements)
        {
            SpriteMovements spriteMovements;
            spriteMovements.reserve(movements.size());
            for (auto& m : movements)
                spriteMovements.emplace_back(grid->toPosition(m.from), grid->toPosition(m.to));
            
            animator->addMovingAnimation(spriteMovements);
        }

        void AnimatedBoardView::drawFrame() const
        {
            for (auto const& itemLoc : selection)
                selectionMarker->drawAt(grid->toPosition(itemLoc));
        }
        
        void AnimatedBoardView::selectItemAt(Position pos)
        {
            if (!grid->isValid(pos) || !animator->isFinished())
                return;

            auto itemLoc = grid->toLocation(pos);
            if (!isItemAlreadySelected(itemLoc))
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

        bool AnimatedBoardView::isItemAlreadySelected(Logic::Location loc)
        {
            return std::find(selection.begin(), selection.end(), loc) != selection.end();
        }
    }
}
