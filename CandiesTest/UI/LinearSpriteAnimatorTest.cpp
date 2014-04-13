#include <UI/LinearSpriteAnimator.hpp>
#include "MockSprite.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct LinearSpriteAnimatorTest : Test
        {
            MockSpritePtr sprite = std::make_shared<StrictMock<MockSprite>>();
            LinearSpriteAnimator animator;
        };
        
        TEST_F(LinearSpriteAnimatorTest, should_draw_the_sprite_at_the_initial_position_when_beginning_the_moving_animation)
        {
            Position FROM{3, 4}, TO{5, 7};
            animator.moveSprite(sprite, FROM, TO);
            
            EXPECT_CALL(*sprite, drawAt(FROM));
            
            animator.draw();
        }
    }
}
