#include <UI/SmoothDisappearingAnimation.hpp>
#include "MockSprite.hpp"
#include "MockDisappearingAnimator.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct SmoothDisappearingAnimationTest : Test
        {
            Position const POS1{1, 1}, POS2{2, 2}, POS3{3, 3}, POS4{4, 4}, POS5{5, 5};
            SpritePtr sprite1 = std::make_shared<StrictMock<MockSprite>>();
            SpritePtr sprite2 = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr sprite3 = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr sprite4 = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr sprite5 = std::make_shared<StrictMock<MockSprite>>();
            
            MockDisappearingAnimatorPtr disappearingAnimator = std::make_shared<StrictMock<MockDisappearingAnimator>>();
            Positions TO_REMOVE{ POS1, POS2 };
            SpritesWithPositions OLD_SPRITES{{sprite3, POS3}, {sprite1, POS1}, {sprite4, POS4}, {sprite2, POS2}, {sprite5, POS5}};
            SpritesWithPositions FINAL_SPRITES{{sprite3, POS3}, {sprite4, POS4}, {sprite5, POS5}};
            
            SmoothDisappearingAnimation create()
            {
                EXPECT_CALL(*disappearingAnimator, addDisappearing(_, _)).Times(AnyNumber());
                
                return SmoothDisappearingAnimation(disappearingAnimator, TO_REMOVE, OLD_SPRITES);
            }
        };
        
        TEST_F(SmoothDisappearingAnimationTest, should_add_disappearing_animations_and_remove_marked_sprites)
        {
            EXPECT_CALL(*disappearingAnimator, addDisappearing(POS1, sprite1));
            EXPECT_CALL(*disappearingAnimator, addDisappearing(POS2, sprite2));
            
            SmoothDisappearingAnimation animation(disappearingAnimator, TO_REMOVE, OLD_SPRITES);
            
            ASSERT_EQ(FINAL_SPRITES, animation.getFinalSprites());
        }
        
        TEST_F(SmoothDisappearingAnimationTest, should_update_the_animations)
        {
            auto animation = create();
            
            EXPECT_CALL(*disappearingAnimator, updateFrame());
            animation.updateFrame();
        }
        
        TEST_F(SmoothDisappearingAnimationTest, should_finish_when_animations_finish)
        {
            auto animation = create();
            
            EXPECT_CALL(*disappearingAnimator, isFinished()).WillRepeatedly(Return(false));
            ASSERT_FALSE(animation.isFinished());
            
            EXPECT_CALL(*disappearingAnimator, isFinished()).WillRepeatedly(Return(true));
            ASSERT_TRUE(animation.isFinished());
        }
        
        TEST_F(SmoothDisappearingAnimationTest, should_draw_animations_and_remaining_sprites)
        {
            auto animation = create();
            
            EXPECT_CALL(*disappearingAnimator, drawFrame());
            EXPECT_CALL(*sprite3, drawAt(POS3));
            EXPECT_CALL(*sprite4, drawAt(POS4));
            EXPECT_CALL(*sprite5, drawAt(POS5));
            
            animation.drawFrame();
        }
    }
}
