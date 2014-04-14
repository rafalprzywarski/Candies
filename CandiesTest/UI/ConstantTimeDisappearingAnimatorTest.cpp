#include <UI/ConstantTimeDisappearingAnimator.hpp>
#include "MockAnimationTimer.hpp"
#include "MockSprite.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct ConstantTimeDisappearingAnimatorTest : Test
        {
            Position FIRST{10, 50}, SECOND{40, 90};
            float const CURRENT_TIME = 100;
            float const ANIMATION_TIME = 4;
            MockSpritePtr sprite = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr sprite2 = std::make_shared<StrictMock<MockSprite>>();
            MockAnimationTimerPtr timer = std::make_shared<StrictMock<MockAnimationTimer>>();
            
            DisappearingAnimatorPtr animator;
            
            void setElapsedTime(float time)
            {
                EXPECT_CALL(*timer, getTime())
                    .WillRepeatedly(Return(CURRENT_TIME + time));
            }
            
            ConstantTimeDisappearingAnimatorTest()
            {
                setElapsedTime(0);
                animator = std::make_shared<ConstantTimeDisappearingAnimator>(timer, ANIMATION_TIME);
            }
            
            void assertDrawWithAlphaAt(MockSpritePtr sprite, float alpha, Position pos)
            {
                EXPECT_CALL(*sprite, drawWithAlphaAt(alpha, pos));
                animator->drawFrame();
            }
        };
        
        TEST_F(ConstantTimeDisappearingAnimatorTest, should_set_initial_alpha_to_1)
        {
            animator->addDisappearing(FIRST, sprite);
            
            assertDrawWithAlphaAt(sprite, 1, FIRST);
        }
        
        TEST_F(ConstantTimeDisappearingAnimatorTest, should_not_fail_when_drawn_empty)
        {
            animator->drawFrame();
        }
        
        TEST_F(ConstantTimeDisappearingAnimatorTest, should_not_fail_when_updated_empty)
        {
            animator->updateFrame();
        }
        
        TEST_F(ConstantTimeDisappearingAnimatorTest, should_fade_alpha_to_zero_during_animation_time)
        {
            animator->addDisappearing(FIRST, sprite);
            
            animator->updateFrame();
            assertDrawWithAlphaAt(sprite, 1, FIRST);
            
            setElapsedTime(ANIMATION_TIME / 2);
            animator->updateFrame();
            
            assertDrawWithAlphaAt(sprite, 0.5f, FIRST);
            
            setElapsedTime(ANIMATION_TIME + 1); // saturate
            animator->updateFrame();
            
            EXPECT_CALL(*sprite, drawWithAlphaAt(0, _)).Times(AtMost(1));
            animator->drawFrame();
        }
        
        TEST_F(ConstantTimeDisappearingAnimatorTest, should_handle_multiple_transitions)
        {
            animator->addDisappearing(FIRST, sprite);
            animator->addDisappearing(SECOND, sprite2);
            
            setElapsedTime(ANIMATION_TIME / 2);
            animator->updateFrame();
            EXPECT_CALL(*sprite, drawWithAlphaAt(0.5f, FIRST));
            EXPECT_CALL(*sprite2, drawWithAlphaAt(0.5f, SECOND));
            
            animator->drawFrame();
        }
        
        TEST_F(ConstantTimeDisappearingAnimatorTest, should_finish_when_animation_time_passed)
        {
            ASSERT_FALSE(animator->isFinished());
            
            animator->addDisappearing(FIRST, sprite);
            animator->addDisappearing(SECOND, sprite2);
            
            ASSERT_FALSE(animator->isFinished());
            
            animator->updateFrame();
            
            ASSERT_FALSE(animator->isFinished());
            
            setElapsedTime(ANIMATION_TIME + 1);
            animator->updateFrame();
            
            ASSERT_TRUE(animator->isFinished());
        }
    }
}
