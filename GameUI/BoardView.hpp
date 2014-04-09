#pragma once
#include "Position.hpp"
#include <GameCore/Location.hpp>
#include <memory>

namespace Candies
{
    namespace UI
    {
        class BoardView
        {
        public:
            virtual ~BoardView() { }
            virtual void selectItemAt(Position pos) = 0;
            virtual GameCore::Locations getSelectedItemLocations() const = 0;
            virtual void clearSelection() = 0;
        };
        
        typedef std::shared_ptr<BoardView> BoardViewPtr;
    }
}
