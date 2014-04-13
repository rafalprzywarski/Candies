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
            Position FROM{3, 4}, TO{5, 7};
            Position FROM2{2, 1}, TO2{13, 4};
            MockSpritePtr sprite = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr sprite2 = std::make_shared<StrictMock<MockSprite>>();
            MockAnimationTimerPtr timer = std::make_shared<StrictMock<MockAnimationTimer>>();
            LinearSpriteAnimator animator{timer, ANIMATION_TIME};
            
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
            EXPECT_CALL(*sprite, drawAt(Position((FROM.x + TO.x) / 2, (FROM.y + TO.y) / 2)));
            
            animator.draw();
        }
        
        TEST_F(LinearSpriteAnimatorTest, should_animate_multiple_sprites_at_the_same_time)
        {
            animator.moveSprite(sprite, FROM, TO);
            setTime(CURRENT_TIME);
            animator.moveSprite(sprite2, FROM2, TO2);
            
            setTimeAndUpdateFrame(CURRENT_TIME + ANIMATION_TIME);
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
        
        TEST_F(LinearSpriteAnimatorTest, should_chain_moving_animations_by_sprite_and_final_position)
        {
            animator.moveSprite(sprite, FROM, TO);
            setTime(CURRENT_TIME + ANIMATION_TIME / 2);
            animator.moveSprite(sprite, TO, TO2);
            
            setTimeAndUpdateFrame(CURRENT_TIME + ANIMATION_TIME / 2);
            EXPECT_CALL(*sprite, drawAt(Position((FROM.x + TO.x) / 2, (FROM.y + TO.y) / 2)));
            
            animator.draw();
            
            setTimeAndUpdateFrame(CURRENT_TIME + ANIMATION_TIME * 1.5f);
            EXPECT_CALL(*sprite, drawAt(Position((TO.x + TO2.x) / 2, (TO.y + TO2.y) / 2)));
            
            animator.draw();
        }
    }
}
