#include <UI/SmoothMovingAnimation.hpp>
#include "MockSprite.hpp"
#include "MockTransitionAnimator.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct SmoothMovingAnimationTest : Test
        {
            Position const POS1a{1, 1}, POS1b{10, 10}, POS2a{2, 2}, POS2b{20, 20}, POS3{3, 3}, POS4{4, 4}, POS5{5, 5};
            SpritePtr sprite1 = std::make_shared<StrictMock<MockSprite>>();
            SpritePtr sprite2 = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr sprite3 = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr sprite4 = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr sprite5 = std::make_shared<StrictMock<MockSprite>>();
            
            MockTransitionAnimatorPtr transitionAnimator = std::make_shared<StrictMock<MockTransitionAnimator>>();
            SpriteMovements MOVEMENTS{{POS1a, POS1b}, {POS2a, POS2b}};
            SpritesWithPositions OLD_SPRITES{{sprite3, POS3}, {sprite1, POS1a}, {sprite4, POS4}, {sprite2, POS2a}, {sprite5, POS5}};
            SpritesWithPositions FINAL_SPRITES{{sprite3, POS3}, {sprite4, POS4}, {sprite5, POS5}, {sprite1, POS1b}, {sprite2, POS2b}};
            
            SmoothMovingAnimation create()
            {
                EXPECT_CALL(*transitionAnimator, addTransition(_, _, _)).Times(AnyNumber());
                
                return SmoothMovingAnimation(transitionAnimator, MOVEMENTS, OLD_SPRITES);
            }
        };
        
        TEST_F(SmoothMovingAnimationTest, should_add_moving_transitions_and_move_the_sprites)
        {
            EXPECT_CALL(*transitionAnimator, addTransition(POS1a, POS1b, sprite1));
            EXPECT_CALL(*transitionAnimator, addTransition(POS2a, POS2b, sprite2));
            
            SmoothMovingAnimation animation(transitionAnimator, MOVEMENTS, OLD_SPRITES);
            
            ASSERT_EQ(FINAL_SPRITES, animation.getFinalSprites());
        }
        
        TEST_F(SmoothMovingAnimationTest, should_update_the_transitions)
        {
            auto animation = create();
            
            EXPECT_CALL(*transitionAnimator, updateFrame());
            animation.updateFrame();
        }
        
        TEST_F(SmoothMovingAnimationTest, should_finish_when_transitions_finish)
        {
            auto animation = create();
            
            EXPECT_CALL(*transitionAnimator, isFinished()).WillRepeatedly(Return(false));
            ASSERT_FALSE(animation.isFinished());
            
            EXPECT_CALL(*transitionAnimator, isFinished()).WillRepeatedly(Return(true));
            ASSERT_TRUE(animation.isFinished());
        }
        
        TEST_F(SmoothMovingAnimationTest, should_draw_transitions_and_not_moving_sprites)
        {
            auto animation = create();
            
            EXPECT_CALL(*transitionAnimator, drawFrame());
            EXPECT_CALL(*sprite3, drawAt(POS3));
            EXPECT_CALL(*sprite4, drawAt(POS4));
            EXPECT_CALL(*sprite5, drawAt(POS5));
            
            animation.drawFrame();
        }
    }
}
