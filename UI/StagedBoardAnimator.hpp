#pragma once
#include "FallingAnimationFactory.hpp"
#include "SwappingAnimationFactory.hpp"
#include "SpriteWithPosition.hpp"
#include <queue>

namespace Candies
{
    namespace UI
    {
        class StagedBoardAnimator
        {
        public:
            StagedBoardAnimator(FallingAnimationFactoryPtr fallingAnimationFactory, SwappingAnimationFactoryPtr swappingAnimationFactory)
            : fallingAnimationFactory(fallingAnimationFactory), swappingAnimationFactory(swappingAnimationFactory) { }
            void addFallingAnimation(const SpritesWithPositions& sprites);
            void addSwappingAnimation(const Position& first, const Position& second);
            void updateFrame();
            void drawFrame() const;
        private:
            std::queue<std::function<AnimationPtr()>> createAnimation;
            FallingAnimationFactoryPtr fallingAnimationFactory;
            SwappingAnimationFactoryPtr swappingAnimationFactory;
            SpritesWithPositions sprites;
            AnimationPtr animation;
        };
    }
}
