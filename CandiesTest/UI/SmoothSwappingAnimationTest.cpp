#include <UI/SmoothSwappingAnimation.hpp>
#include "MockSprite.hpp"
#include "MockTransitionAnimator.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct SmoothSwappingAnimationTest : Test
        {
            Position FIRST{4, 5}, SECOND{2, 5};
            SpritePtr sprite1 = std::make_shared<StrictMock<MockSprite>>();
            SpritePtr sprite2 = std::make_shared<StrictMock<MockSprite>>();
            SpritePtr sprite3 = std::make_shared<StrictMock<MockSprite>>();
            SpritePtr sprite4 = std::make_shared<StrictMock<MockSprite>>();

            MockTransitionAnimatorPtr transitionAnimator = std::make_shared<StrictMock<MockTransitionAnimator>>();
            SpritesWithPositions SPRITES{{sprite1, SECOND}, {sprite2, {6, 6}}, {sprite3, FIRST}, {sprite4, {2, 3}}};
            SpritesWithPositions FINAL_SPRITES{{sprite1, FIRST}, {sprite2, {6, 6}}, {sprite3, SECOND}, {sprite4, {2, 3}}};
            
            SmoothSwappingAnimation create()
            {
                EXPECT_CALL(*transitionAnimator, addTransition(_, _, _)).Times(AnyNumber());
                
                return SmoothSwappingAnimation(transitionAnimator, FIRST, SECOND, SPRITES);
            }
        };
        
        TEST_F(SmoothSwappingAnimationTest, should_swap_selected_sprite_positions_and_add_swapping_transitions)
        {
            EXPECT_CALL(*transitionAnimator, addTransition(FIRST, SECOND, sprite3));
            EXPECT_CALL(*transitionAnimator, addTransition(SECOND, FIRST, sprite1));

            SmoothSwappingAnimation animation(transitionAnimator, FIRST, SECOND, SPRITES);
            
            ASSERT_EQ(FINAL_SPRITES, animation.getFinalSprites());
        }
        
        TEST_F(SmoothSwappingAnimationTest, should_update_the_transitions)
        {
            auto animation = create();
            
            EXPECT_CALL(*transitionAnimator, updateFrame());
            animation.updateFrame();
        }
        
        TEST_F(SmoothSwappingAnimationTest, should_finish_when_transitions_finish)
        {
            auto animation = create();
            
            EXPECT_CALL(*transitionAnimator, isFinished()).WillRepeatedly(Return(false));
            ASSERT_FALSE(animation.isFinished());

            EXPECT_CALL(*transitionAnimator, isFinished()).WillRepeatedly(Return(true));
            ASSERT_TRUE(animation.isFinished());
        }
    }
}
