#pragma once
#include <UI/BoardAnimator.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockBoardAnimator : BoardAnimator
        {
            MOCK_METHOD1(addFallingAnimation, void(const SpritesWithPositions& sprites));
            MOCK_METHOD1(addMovingAnimation, void(const SpriteMovements& movements));
            MOCK_METHOD2(addSwappingAnimation, void(const Position& first, const Position& second));
            MOCK_METHOD1(addDisappearingAnimation, void(const Positions& positions));
            MOCK_CONST_METHOD0(isFinished, bool());
        };
        
        typedef std::shared_ptr<MockBoardAnimator> MockBoardAnimatorPtr;
    }
}
