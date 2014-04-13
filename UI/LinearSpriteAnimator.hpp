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
                Position from, to, position;

                SpriteState(SpritePtr sprite, Position from, Position to)
                : sprite(sprite), from(from), to(to), position(from)
                { }
                
                void draw() const;
                void update(float completionFactor);
            };

            AnimationTimerPtr timer;
            float animationTime;
            std::vector<SpriteState> sprites;
            float startTime{0};
            
            static int lerp(int from, int to, float t);
            static Position lerp(Position from, Position to, float t);
        };
    }
}
