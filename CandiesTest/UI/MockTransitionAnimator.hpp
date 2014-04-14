#pragma once
#include <UI/TransitionAnimator.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockTransitionAnimator : TransitionAnimator
        {
            MOCK_METHOD3(addTransition, void(Position first, Position second, SpritePtr sprite));
            MOCK_METHOD0(updateFrame, void());
            MOCK_CONST_METHOD0(drawFrame, void());
            MOCK_CONST_METHOD0(isFinished, bool());
        };
        
        typedef std::shared_ptr<MockTransitionAnimator> MockTransitionAnimatorPtr;
    }
}
