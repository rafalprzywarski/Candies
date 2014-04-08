#pragma once
#include <GameCore/ItemId.hpp>
#include <GameCore/Location.hpp>
#include "Sprite.hpp"
#include "Position.hpp"
#include <memory>
#include <unordered_map>
#include <vector>

namespace Candies
{
    namespace UI
    {
        class StaticBoard
        {
        public:
            StaticBoard(std::vector<std::pair<const GameCore::ItemId, SpritePtr>> sprites, int gridSize, Position position);
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
    }
}
