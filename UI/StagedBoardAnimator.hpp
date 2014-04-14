#pragma once
#include "FallingAnimationFactory.hpp"
#include "SwappingAnimationFactory.hpp"
#include "DisappearingAnimationFactory.hpp"
#include "SpriteWithPosition.hpp"
#include "UpdateFrameListener.hpp"
#include "DrawFrameListener.hpp"
#include "BoardAnimator.hpp"
#include <queue>

namespace Candies
{
    namespace UI
    {
        class StagedBoardAnimator : public BoardAnimator, public DrawFrameListener, UpdateFrameListener
        {
        public:
            StagedBoardAnimator(FallingAnimationFactoryPtr fallingAnimationFactory, SwappingAnimationFactoryPtr swappingAnimationFactory, DisappearingAnimationFactoryPtr disappearingAnimationFactory)
            : fallingAnimationFactory(fallingAnimationFactory), swappingAnimationFactory(swappingAnimationFactory), disappearingAnimationFactory(disappearingAnimationFactory) { }
            void addFallingAnimation(const SpritesWithPositions& sprites);
            void addSwappingAnimation(const Position& first, const Position& second);
            void addDisappearingAnimation(const Positions& positions);
            void updateFrame();
            void drawFrame() const;
            bool isFinished() const;
        private:
            std::queue<std::function<AnimationPtr(const SpritesWithPositions& finalSprites)>> createAnimation;
            FallingAnimationFactoryPtr fallingAnimationFactory;
            SwappingAnimationFactoryPtr swappingAnimationFactory;
            DisappearingAnimationFactoryPtr disappearingAnimationFactory;
            SpritesWithPositions sprites;
            AnimationPtr animation;
            
            bool shouldCreateNewAnimation() const;
            void createNewAnimation();
        };
    }
}
