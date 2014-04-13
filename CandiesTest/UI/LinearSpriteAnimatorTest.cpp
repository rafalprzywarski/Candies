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
            const float ANIMATION_VELOCITY = 0.25;
            const float CURRENT_TIME = 100;
            Position FROM{30, 50}, TO{60, 90};
            Position HALFWAY_BETWEEN_FROM_TO{45, 70};
            Position FROM2{20, 1}, TO2{50, -40};
            Position THIRD_BETWEEN_TO_TO2{57, 47};
            const float DISTANCE = 50; // |FROM - TO| == [FROM2 - TO2|
            const float ANIMATION_TIME = DISTANCE / ANIMATION_VELOCITY;
            const float ANIMATION_TIME_TO_TO2 = 130.384048104053f / ANIMATION_VELOCITY;
            const float ANIMATION_TIME_TO_FROM2 = 89.44271909999159f / ANIMATION_VELOCITY;
            MockSpritePtr sprite = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr sprite2 = std::make_shared<StrictMock<MockSprite>>();
            MockAnimationTimerPtr timer = std::make_shared<StrictMock<MockAnimationTimer>>();
            LinearSpriteAnimator animator{timer, ANIMATION_VELOCITY};
            
            void setTime(float time)
            {
                EXPECT_CALL(*timer, getTime()).Times(AtMost(1)).WillRepeatedly(Return(time)).RetiresOnSaturation();
            }
            
            LinearSpriteAnimatorTest()
            {
                setTime(CURRENT_TIME);
            }
            
            void setTimeAndUpdateFrame(float time)
            {
                setTime(time);
                animator.updateFrame();
            }
        };
        
        TEST_F(LinearSpriteAnimatorTest, should_draw_the_sprite_at_the_initial_position_when_beginning_the_moving_animation)
        {
            animator.moveSprite(sprite, FROM, TO);
            
            EXPECT_CALL(*sprite, drawAt(FROM));
            
            animator.draw();
        }
        
        TEST_F(LinearSpriteAnimatorTest, should_draw_the_sprite_at_the_final_position_when_the_moving_animation_finishes)
        {
            animator.moveSprite(sprite, FROM, TO);

            setTimeAndUpdateFrame(CURRENT_TIME + ANIMATION_TIME + 1);
            EXPECT_CALL(*sprite, drawAt(TO));
            
            animator.draw();
        }
        
        TEST_F(LinearSpriteAnimatorTest, should_lerp_sprite_position_during_animation)
        {
            animator.moveSprite(sprite, FROM, TO);
            
            setTimeAndUpdateFrame(CURRENT_TIME);
            EXPECT_CALL(*sprite, drawAt(FROM));
            
            animator.draw();
            
            setTimeAndUpdateFrame(CURRENT_TIME + ANIMATION_TIME / 2);
            EXPECT_CALL(*sprite, drawAt(HALFWAY_BETWEEN_FROM_TO));
            
            animator.draw();
        }
        
        TEST_F(LinearSpriteAnimatorTest, should_animate_multiple_sprites_at_the_same_time)
        {
            animator.moveSprite(sprite, FROM, TO);
            setTime(CURRENT_TIME);
            animator.moveSprite(sprite2, FROM2, TO2);
            
            setTimeAndUpdateFrame(CURRENT_TIME + ANIMATION_TIME + 1);
            EXPECT_CALL(*sprite, drawAt(TO));
            EXPECT_CALL(*sprite2, drawAt(TO2));
            
            animator.draw();
        }
        
        TEST_F(LinearSpriteAnimatorTest, should_allow_moving_at_any_time)
        {
            animator.moveSprite(sprite, FROM, TO);
            setTime(CURRENT_TIME + ANIMATION_TIME / 2);
            animator.moveSprite(sprite2, FROM2, TO2);
            
            setTimeAndUpdateFrame(CURRENT_TIME + ANIMATION_TIME / 2);
            EXPECT_CALL(*sprite, drawAt(Not(FROM)));
            EXPECT_CALL(*sprite2, drawAt(FROM2));

            animator.draw();
        }
        
        TEST_F(LinearSpriteAnimatorTest, should_chain_moving_animations_by_sprite_final_position)
        {
            animator.moveSprite(sprite, FROM, TO);
            animator.moveSprite(sprite, TO, TO2);
            
            setTimeAndUpdateFrame(CURRENT_TIME + ANIMATION_TIME / 2);
            EXPECT_CALL(*sprite, drawAt(HALFWAY_BETWEEN_FROM_TO));
            
            animator.draw();
            
            setTimeAndUpdateFrame(CURRENT_TIME + ANIMATION_TIME + ANIMATION_TIME_TO_TO2 / 3);
            EXPECT_CALL(*sprite, drawAt(THIRD_BETWEEN_TO_TO2));
            
            animator.draw();
        }
        
        TEST_F(LinearSpriteAnimatorTest, should_chain_moving_even_after_previous_animation_finished)
        {
            animator.moveSprite(sprite, FROM, TO);
            setTimeAndUpdateFrame(CURRENT_TIME + ANIMATION_TIME * 5);
            animator.moveSprite(sprite, TO, TO2);
            setTimeAndUpdateFrame(CURRENT_TIME + ANIMATION_TIME * 5 + ANIMATION_TIME_TO_TO2);
            
            EXPECT_CALL(*sprite, drawAt(_)).Times(1);
            
            animator.draw();
        }
        
        TEST_F(LinearSpriteAnimatorTest, should_allowing_moving_different_instances_of_the_same_sprite)
        {
            animator.moveSprite(sprite, FROM, TO);
            setTime(CURRENT_TIME);
            animator.moveSprite(sprite, FROM2, TO2);
            
            EXPECT_CALL(*sprite, drawAt(FROM));
            EXPECT_CALL(*sprite, drawAt(FROM2));
            
            animator.draw();
        }
        
        TEST_F(LinearSpriteAnimatorTest, should_skip_animation_stages)
        {
            animator.moveSprite(sprite, FROM, TO);
            animator.moveSprite(sprite, TO, FROM2);
            animator.moveSprite(sprite, FROM2, TO2);
            
            setTimeAndUpdateFrame(CURRENT_TIME + ANIMATION_TIME + ANIMATION_TIME_TO_FROM2 + ANIMATION_TIME);
            EXPECT_CALL(*sprite, drawAt(TO2));
            
            animator.draw();
        }
        
        TEST_F(LinearSpriteAnimatorTest, should_chain_destruction_of_sprites)
        {
            animator.moveSprite(sprite, FROM, TO);
            animator.moveSprite(sprite, TO, TO2);
            setTime(CURRENT_TIME);
            animator.moveSprite(sprite, FROM2, TO);

            animator.destroySpriteAt(sprite, TO2);
            EXPECT_CALL(*sprite, drawAt(_)).Times(2);
            
            animator.draw();
            
            setTimeAndUpdateFrame(CURRENT_TIME + ANIMATION_TIME + ANIMATION_TIME_TO_TO2);
            EXPECT_CALL(*sprite, drawAt(_)).Times(1);
            
            animator.draw();
        }
    }
}
