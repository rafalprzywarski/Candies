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
            Position FIRST{10, 50}, SECOND{40, 90};
            Position FIRST_SECOND_MIDPOINT{(FIRST.x + SECOND.x) / 2, (FIRST.y + SECOND.y) / 2};
            float const FIRST_SECOND_DISTANCE = 50;
            float const CURRENT_TIME = 100;
            float const VELOCITY = 4;
            Position FIRST2{30, 100}, SECOND2{90, 180};
            float const FIRST2_SECOND2_DISTANCE = 100;
            MockSpritePtr sprite = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr sprite2 = std::make_shared<StrictMock<MockSprite>>();
            MockAnimationTimerPtr timer = std::make_shared<StrictMock<MockAnimationTimer>>();

            ConstantVelocityTransitionAnimator animator{timer, VELOCITY};
            
            void setElapsedTime(float time)
            {
                EXPECT_CALL(*timer, getTime())
                    .WillRepeatedly(Return(CURRENT_TIME + time)).RetiresOnSaturation();
            }
            
            ConstantVelocityTransitionAnimatorTest()
            {
                setElapsedTime(0);
            }
            
            void assertDrawAt(MockSpritePtr sprite, Position pos)
            {
                EXPECT_CALL(*sprite, drawAt(pos));
                animator.drawFrame();
            }
        };
        
        TEST_F(ConstantVelocityTransitionAnimatorTest, should_set_first_position_as_the_initial_position)
        {
            animator.addTransition(FIRST, SECOND, sprite);
            
            assertDrawAt(sprite, FIRST);
        }
        
        TEST_F(ConstantVelocityTransitionAnimatorTest, should_not_fail_when_drawn_empty)
        {
            animator.drawFrame();
        }

        TEST_F(ConstantVelocityTransitionAnimatorTest, should_not_fail_when_updated_empty)
        {
            animator.updateFrame();
        }
        
        TEST_F(ConstantVelocityTransitionAnimatorTest, should_interpolate_position_according_to_time)
        {
            animator.addTransition(FIRST, SECOND, sprite);

            animator.updateFrame();
            assertDrawAt(sprite, FIRST);
            
            setElapsedTime(FIRST_SECOND_DISTANCE / VELOCITY / 2);
            animator.updateFrame();

            assertDrawAt(sprite, FIRST_SECOND_MIDPOINT);

            setElapsedTime(FIRST_SECOND_DISTANCE / VELOCITY + 1); // saturate
            animator.updateFrame();
            
            assertDrawAt(sprite, SECOND);
        }
        
        TEST_F(ConstantVelocityTransitionAnimatorTest, should_handle_multiple_transitions)
        {
            animator.addTransition(FIRST, SECOND, sprite);
            
            setElapsedTime(FIRST_SECOND_DISTANCE / VELOCITY / 2);
            animator.addTransition(FIRST2, SECOND2, sprite2);
            
            animator.updateFrame();
            
            InSequence order;
            EXPECT_CALL(*sprite, drawAt(FIRST_SECOND_MIDPOINT));
            EXPECT_CALL(*sprite2, drawAt(FIRST2));
            animator.drawFrame();
        }
        
        TEST_F(ConstantVelocityTransitionAnimatorTest, should_when_there_are_no_active_transitions)
        {
            ASSERT_TRUE(animator.isFinished());
            
            animator.addTransition(FIRST, SECOND, sprite);
            animator.addTransition(FIRST2, SECOND2, sprite2);
            
            ASSERT_FALSE(animator.isFinished());

            setElapsedTime(FIRST_SECOND_DISTANCE / VELOCITY + 1);
            animator.updateFrame();
            
            ASSERT_FALSE(animator.isFinished());

            setElapsedTime(FIRST2_SECOND2_DISTANCE / VELOCITY + 1);
            animator.updateFrame();
            
            ASSERT_TRUE(animator.isFinished());
        }
    }
}
