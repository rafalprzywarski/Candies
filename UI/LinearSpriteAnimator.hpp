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
            LinearSpriteAnimator(AnimationTimerPtr timer, float animationVelocity)
            : timer(timer), animationVelocity(animationVelocity) { }
            void moveSprite(SpritePtr sprite, Position from, Position to);
            void swapSprites(SpritePtr sprite1, Position from1, SpritePtr sprite2, Position from2);
            void destroySpriteAt(SpritePtr sprite, Position at);
            bool isAnimating() const;
            void draw() const;
            void updateFrame();
        private:
            class AnimatedSprite
            {
            public:
                AnimatedSprite(SpritePtr sprite, Position from, float fromTime, float velocity)
                : sprite(sprite), from(from), position(from), fromTime(fromTime), velocity(velocity), shouldBeDestroyed(false)
                { }
                
                void draw() const;
                void update(float currentTime);
                bool isDestroyed() const;
                bool shouldChainWith(Position from) const;
                void addTransition(Position to);
                void markForDestruction();
            private:
                SpritePtr sprite;
                Position from, position;
                std::vector<Position> destinations;
                float fromTime, velocity;
                bool shouldBeDestroyed;
                
                void finishCurrentTransition(float currentTransitionLength);
                float getCurrentDistance(float currentTime) const;
            };

            AnimationTimerPtr timer;
            float animationVelocity;
            std::vector<AnimatedSprite> sprites;
            
            bool chainSprite(SpritePtr sprite, Position from, Position to);
            void addNewSprite(SpritePtr sprite, Position from, Position to, float currentTime);
            static int lerp(int from, int to, float t);
            static Position lerp(Position from, Position to, float t);
            static float distance(Position from, Position to);
        };
    }
}
