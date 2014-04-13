#pragma once
#include "SpriteAnimator.hpp"
#include "UpdateFrameListener.hpp"
#include "AnimationTimer.hpp"
#include <vector>

namespace Candies
{
    namespace UI
    {
        class LinearSpriteAnimator : public SpriteAnimator, public UpdateFrameListener
        {
        public:
            LinearSpriteAnimator(AnimationTimerPtr timer, float animationTime)
            : timer(timer), animationTime(animationTime) { }
            void moveSprite(SpritePtr sprite, Position from, Position to);
            void destroySpriteAt(SpritePtr sprite, Position at);
            bool isAnimating() const;
            void draw() const;
            void updateFrame();
        private:
            struct SpriteState
            {
                SpritePtr sprite;
                Position from, position;
                std::vector<Position> destinations;
                float startTime;
                bool shouldBeDestroyed;

                SpriteState(SpritePtr sprite, Position from, Position to, float startTime)
                : sprite(sprite), from(from), destinations({to}), position(from), startTime(startTime), shouldBeDestroyed(false)
                { }
                
                void draw() const;
                void update(float currentTime);
                bool isDestroyed() const;
                bool shouldChainWith(Position from)
                {
                    return (!destinations.empty() && destinations.back() == from) || position == from;
                }
                void chain(Position to)
                {
                    destinations.push_back(to);
                }
            };

            AnimationTimerPtr timer;
            float animationTime;
            std::vector<SpriteState> sprites;
            
            static int lerp(int from, int to, float t);
            static Position lerp(Position from, Position to, float t);
        };
    }
}
