#include <UI/SmoothFallingAnimation.hpp>
#include "MockSprite.hpp"
#include "MockTransitionAnimator.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct SmoothFallingAnimationTest : Test
        {
            const int FALLING_HEIGHT = -20;
            Position const POS1{1, 1}, POS2{2, 2};
            MockSpritePtr sprite1 = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr sprite2 = std::make_shared<StrictMock<MockSprite>>();
            SpritePtr sprite3 = std::make_shared<StrictMock<MockSprite>>();
            SpritePtr sprite4 = std::make_shared<StrictMock<MockSprite>>();
            SpritePtr sprite5 = std::make_shared<StrictMock<MockSprite>>();
            
            MockTransitionAnimatorPtr transitionAnimator = std::make_shared<StrictMock<MockTransitionAnimator>>();
            SpritesWithPositions OLD_SPRITES{{sprite1, POS1}, {sprite2, POS2}};
            SpritesWithPositions NEW_SPRITES{{sprite3, {3, 3}}, {sprite4, {4, 8}}, {sprite5, {5, 5}}};
            const int LOWEST_Y = 8; // y axis points down
            SpritesWithPositions FINAL_SPRITES{{sprite1, POS1}, {sprite2, POS2}, {sprite3, {3, 3}}, {sprite4, {4, 8}}, {sprite5, {5, 5}}};
            
            SmoothFallingAnimation create()
            {
                EXPECT_CALL(*transitionAnimator, addTransition(_, _, _)).Times(AnyNumber());
                
                return SmoothFallingAnimation(transitionAnimator, FALLING_HEIGHT, NEW_SPRITES, OLD_SPRITES);
            }
            
            Position movedUp(Position p, int by)
            {
                p.y -= by;
                return p;
            }
        };
        
        TEST_F(SmoothFallingAnimationTest, should_add_falling_transitions_and_merge_sprite_lists)
        {
            auto HEIGHT_DELTA = LOWEST_Y - FALLING_HEIGHT;
            EXPECT_CALL(*transitionAnimator, addTransition(movedUp(NEW_SPRITES[0].position, HEIGHT_DELTA), NEW_SPRITES[0].position, NEW_SPRITES[0].sprite));
            EXPECT_CALL(*transitionAnimator, addTransition(movedUp(NEW_SPRITES[1].position, HEIGHT_DELTA), NEW_SPRITES[1].position, NEW_SPRITES[1].sprite));
            EXPECT_CALL(*transitionAnimator, addTransition(movedUp(NEW_SPRITES[2].position, HEIGHT_DELTA), NEW_SPRITES[2].position, NEW_SPRITES[2].sprite));
            
            SmoothFallingAnimation animation(transitionAnimator, FALLING_HEIGHT, NEW_SPRITES, OLD_SPRITES);
            
            ASSERT_EQ(FINAL_SPRITES, animation.getFinalSprites());
        }
        
        TEST_F(SmoothFallingAnimationTest, should_update_the_transitions)
        {
            auto animation = create();
            
            EXPECT_CALL(*transitionAnimator, updateFrame());
            animation.updateFrame();
        }
        
        TEST_F(SmoothFallingAnimationTest, should_finish_when_transitions_finish)
        {
            auto animation = create();
            
            EXPECT_CALL(*transitionAnimator, isFinished()).WillRepeatedly(Return(false));
            ASSERT_FALSE(animation.isFinished());
            
            EXPECT_CALL(*transitionAnimator, isFinished()).WillRepeatedly(Return(true));
            ASSERT_TRUE(animation.isFinished());
        }
        
        TEST_F(SmoothFallingAnimationTest, should_draw_transitions_and_old_sprites)
        {
            auto animation = create();
            
            EXPECT_CALL(*transitionAnimator, drawFrame());
            EXPECT_CALL(*sprite1, drawAt(POS1));
            EXPECT_CALL(*sprite2, drawAt(POS2));
            
            animation.drawFrame();
        }
        
        TEST_F(SmoothFallingAnimationTest, should_fail_when_given_no_new_sprites)
        {
            ASSERT_THROW(SmoothFallingAnimation(transitionAnimator, FALLING_HEIGHT, {}, OLD_SPRITES), std::invalid_argument);
        }
    }
}
