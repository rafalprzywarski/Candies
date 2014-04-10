#pragma once
#include <Logic/ItemId.hpp>
#include <Logic/Location.hpp>
#include "Sprite.hpp"
#include "Position.hpp"
#include "FrameUpdateListener.hpp"
#include "BoardView.hpp"
#include <memory>
#include <unordered_map>
#include <vector>

namespace Candies
{
    namespace UI
    {
        class StaticBoardView : public FrameUpdateListener, public BoardView
        {
        public:
            typedef std::vector<std::pair<const Logic::ItemId, SpritePtr>> Sprites;
            StaticBoardView(Sprites sprites, SpritePtr selectionMarker, int gridSize, Position origin);
            void addItem(Logic::ItemId id, Logic::Location loc);
            void swapItems(Logic::Location loc1, Logic::Location loc2);
            void removeItem(Logic::Location loc);
            void update();
            void selectItemAt(Position pos);
            Logic::Locations getSelectedItemLocations() const;
            void clearSelection();
        private:
            std::unordered_map<Logic::ItemId, SpritePtr> sprites;
            SpritePtr selectionMarker;
            std::unordered_map<Logic::Location, SpritePtr> items;
            std::vector<Logic::Location> selection;
            int gridSize;
            Position origin;
            
            Position toPosition(Logic::Location loc);
            Logic::Location toLocation(Position pos);
            bool itemExists(Logic::Location loc);
            bool isItemAlreadySelected(Logic::Location loc);
        };
        
        typedef std::shared_ptr<StaticBoardView> StaticBoardViewPtr;
    }
}
