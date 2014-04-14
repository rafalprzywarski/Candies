#pragma once
#include "DrawFrameListener.hpp"
#include "AnimationTimer.hpp"
#include "Sprite.hpp"
#include <vector>

namespace Candies
{
    namespace UI
    {
        struct SpriteWithPosition
        {
            SpritePtr sprite;
            Position position;
            SpriteWithPosition(SpritePtr sprite, Position position)
            : sprite(std::move(sprite)), position(position) { }
        };
        
        typedef std::vector<SpriteWithPosition> SpritesWithPositions;

        class ConstantVelocityBoardAnimator : public DrawFrameListener
        {
        public:
            ConstantVelocityBoardAnimator(AnimationTimerPtr timer, int fallingHeight)
            : timer(std::move(timer)), fallingHeight(fallingHeight) { }
            void addItems(const SpritesWithPositions& newSprites);
            void drawFrame() const;
        private:
            AnimationTimerPtr timer;
            int fallingHeight;
            SpritesWithPositions sprites;
            
            static int getLowestHeight(const SpritesWithPositions& sprites);
        };
    }
}
