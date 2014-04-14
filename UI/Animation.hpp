#pragma once
#include "SpriteWithPosition.hpp"
#include <memory>

namespace Candies
{
    namespace UI
    {
        class Animation
        {
        public:
            virtual ~Animation() { }
            virtual void updateFrame() = 0;
            virtual void drawFrame() const = 0;
            virtual bool isFinished() const = 0;
            virtual SpritesWithPositions getFinalSprites() const = 0;
        };
        
        typedef std::shared_ptr<Animation> AnimationPtr;
    }
}
