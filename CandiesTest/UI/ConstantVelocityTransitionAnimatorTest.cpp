#include <UI/ConstantVelocityTransitionAnimator.hpp>
#include "MockAnimationTimer.hpp"
#include "MockSprite.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct ConstantVelocityTransitionAnimatorTest : Test
        {
            Position FIRST{10, 5}, SECOND{20, 5};
            float const VELOCITY = 4;
            MockSpritePtr sprite = std::make_shared<StrictMock<MockSprite>>();
            MockAnimationTimerPtr timer = std::make_shared<StrictMock<MockAnimationTimer>>();

            ConstantVelocityTransitionAnimator animator{timer};
        };
        
        TEST_F(ConstantVelocityTransitionAnimatorTest, should_set_first_position_as_the_initial_position)
        {
            animator.addTransition(FIRST, SECOND, sprite);
            
            EXPECT_CALL(*sprite, drawAt(FIRST));
            animator.drawFrame();
        }
    }
}
