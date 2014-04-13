#include <UI/LinearSpriteAnimator.hpp>
#include "MockAnimationTimer.hpp"
#include "MockSprite.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct LinearSpriteAnimatorTest : Test
        {
            const float ANIMATION_TIME = 1;
            const float CURRENT_TIME = 100;
            MockSpritePtr sprite = std::make_shared<StrictMock<MockSprite>>();
            MockAnimationTimerPtr timer = std::make_shared<StrictMock<MockAnimationTimer>>();
            LinearSpriteAnimator animator{timer, ANIMATION_TIME};
            
            void setTime(float time)
            {
                EXPECT_CALL(*timer, getTime()).Times(AtMost(1)).WillRepeatedly(Return(time));
            }
            
            LinearSpriteAnimatorTest()
            {
                setTime(CURRENT_TIME);
            }
        };
        
        TEST_F(LinearSpriteAnimatorTest, should_draw_the_sprite_at_the_initial_position_when_beginning_the_moving_animation)
        {
            Position FROM{3, 4}, TO{5, 7};
            animator.moveSprite(sprite, FROM, TO);
            
            EXPECT_CALL(*sprite, drawAt(FROM));
            
            animator.draw();
        }
        
        TEST_F(LinearSpriteAnimatorTest, should_draw_the_sprite_at_the_final_position_when_the_moving_animation_finishes)
        {
            Position FROM{3, 4}, TO{5, 7};
            animator.moveSprite(sprite, FROM, TO);

            setTime(CURRENT_TIME + ANIMATION_TIME + 1);
            animator.updateFrame();
            
            EXPECT_CALL(*sprite, drawAt(TO));
            
            animator.draw();
        }
    }
}
