#pragma once
#include "SpriteWithPosition.hpp"
#include "Animation.hpp"
#include <memory>

namespace Candies
{
    namespace UI
    {
        class SwappingAnimationFactory
        {
        public:
            virtual ~SwappingAnimationFactory() { }
            virtual AnimationPtr createAnimation(Position first, Position second, const SpritesWithPositions& oldSprites) = 0;
        };
        
        typedef std::shared_ptr<SwappingAnimationFactory> SwappingAnimationFactoryPtr;
    }
}
