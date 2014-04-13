#pragma once
#include "Position.hpp"
#include <Logic/Location.hpp>
#include <memory>

namespace Candies
{
    namespace UI
    {
        class Grid
        {
        public:
            virtual ~Grid() { }
            virtual Position toPosition(Logic::Location loc) const = 0;
            virtual bool isValid(Position pos) const = 0;
            virtual Logic::Location toLocation(Position pos) const = 0;
        };
        
        typedef std::shared_ptr<Grid> GridPtr;
    }
}
