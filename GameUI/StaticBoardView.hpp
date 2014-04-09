#pragma once
#include <GameCore/ItemId.hpp>
#include <GameCore/Location.hpp>
#include "Sprite.hpp"
#include "Position.hpp"
#include "FrameUpdateListener.hpp"
#include <memory>
#include <unordered_map>
#include <vector>

namespace Candies
{
    namespace UI
    {
        class StaticBoardView : public FrameUpdateListener
        {
        public:
            typedef std::vector<std::pair<const GameCore::ItemId, SpritePtr>> Sprites;
            StaticBoardView(Sprites sprites, int gridSize, Position position);
            void addItem(GameCore::ItemId id, GameCore::Location loc);
            void update();
        private:
            struct SpriteWithLocation
            {
                SpritePtr sprite;
                GameCore::Location location;
            };
            std::unordered_map<GameCore::ItemId, SpritePtr> sprites;
            std::vector<SpriteWithLocation> items;
            int gridSize;
            Position position;
        };
        
        typedef std::shared_ptr<StaticBoardView> StaticBoardViewPtr;
    }
}
