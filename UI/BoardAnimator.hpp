#pragma once
#include "SpriteWithPosition.hpp"
#include "UpdateFrameListener.hpp"
#include "DrawFrameListener.hpp"
#include <queue>

namespace Candies
{
    namespace UI
    {
        class BoardAnimator
        {
        public:
            virtual ~BoardAnimator() { }
            virtual void addFallingAnimation(const SpritesWithPositions& sprites) = 0;
            virtual void addSwappingAnimation(const Position& first, const Position& second) = 0;
            virtual void addDisappearingAnimation(const Positions& positions) = 0;
            virtual bool isFinished() const = 0;
        };
    }
}
