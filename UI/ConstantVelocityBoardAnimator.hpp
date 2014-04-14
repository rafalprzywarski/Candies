#pragma once
#include "DrawFrameListener.hpp"
#include "UpdateFrameListener.hpp"
#include "AnimationTimer.hpp"
#include "TimedInterpolator.hpp"
#include "Sprite.hpp"
#include "SpriteWithPosition.hpp"
#include <vector>

namespace Candies
{
    namespace UI
    {
        class ConstantVelocityBoardAnimator : public DrawFrameListener
        {
        public:
            ConstantVelocityBoardAnimator(AnimationTimerPtr timer, TimedInterpolatorPtr interpolator, int fallingHeight)
            : timer(std::move(timer)), interpolator(interpolator), fallingHeight(fallingHeight) { }
            void addItems(const SpritesWithPositions& newSprites);
            void drawFrame() const;
            void updateFrame();
        private:
            struct AnimatedSprite
            {
                SpritePtr sprite;
                int startingHeight;
                Position finalPosition, position;
                AnimatedSprite(SpritePtr sprite, int startingHeight, Position finalPosition)
                : sprite(sprite), startingHeight(startingHeight), finalPosition(finalPosition),
                position(finalPosition.x, startingHeight) { }
            };
            AnimationTimerPtr timer;
            TimedInterpolatorPtr interpolator;
            int fallingHeight;
            float startTime{};
            std::vector<AnimatedSprite> sprites;
            
            static int getLowestHeight(const SpritesWithPositions& sprites);
        };
    }
}
