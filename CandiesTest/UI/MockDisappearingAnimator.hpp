#pragma once
#include <UI/DisappearingAnimator.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockDisappearingAnimator : DisappearingAnimator
        {
            MOCK_METHOD2(addDisappearing, void(Position pos, SpritePtr sprite));
            MOCK_METHOD0(updateFrame, void());
            MOCK_CONST_METHOD0(drawFrame, void());
            MOCK_CONST_METHOD0(isFinished, bool());
        };
        
        typedef std::shared_ptr<MockDisappearingAnimator> MockDisappearingAnimatorPtr;
    }
}
