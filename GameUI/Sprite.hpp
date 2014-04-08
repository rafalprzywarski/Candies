#pragma once
#include "Position.hpp"
#include <memory>

namespace Candies
{
    namespace UI
    {
        class Sprite
        {
        public:
            virtual ~Sprite() { }
            virtual void drawAt(Position p) = 0;
        };
        
        typedef std::shared_ptr<Sprite> SpritePtr;
    }
}
