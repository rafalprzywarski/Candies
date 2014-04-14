#pragma once
#include <Logic/ItemId.hpp>
#include <Logic/Location.hpp>
#include "Sprite.hpp"
#include "Position.hpp"
#include "DrawFrameListener.hpp"
#include "BoardView.hpp"
#include "Grid.hpp"
#include "BoardAnimator.hpp"
#include "GameObserver.hpp"
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Candies
{
    namespace UI
    {
        class AnimatedBoardView : public DrawFrameListener, public BoardView
        {
        public:
            typedef std::vector<std::pair<const Logic::ItemId, SpritePtr>> Sprites;
            AnimatedBoardView(Sprites sprites, SpritePtr selectionMarker, GridPtr grid, BoardAnimatorPtr animator);
            void addItems(const Logic::ItemIdsWithLocations& items);
            void swapItems(Logic::Location loc1, Logic::Location loc2);
            void dontSwapItems(Logic::Location loc1, Logic::Location loc2);
            void removeItems(const Logic::Locations& locs);
            void moveItems(const Logic::Movements& movements);
            void drawFrame() const;
            void selectItemAt(Position pos);
            Logic::Locations getSelectedItemLocations() const;
            void clearSelection();
        private:
            
            std::unordered_map<Logic::ItemId, SpritePtr> sprites;
            SpritePtr selectionMarker;
            GridPtr grid;
            std::vector<Logic::Location> selection;
            BoardAnimatorPtr animator;

            bool isItemAlreadySelected(Logic::Location loc);
        };
        
        typedef std::shared_ptr<AnimatedBoardView> AnimatedBoardViewPtr;
    }
}
