#include <UI/StagedBoardAnimator.hpp>
#include "MockFallingAnimationFactory.hpp"
#include "MockSwappingAnimationFactory.hpp"
#include "MockDisappearingAnimationFactory.hpp"
#include "MockAnimation.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct StagedBoardAnimatorTest : Test
        {
            SpritesWithPositions SPRITES{{nullptr, {4, 5}}};
            SpritesWithPositions NOTHING;
            SpritesWithPositions FINAL_SPRITES{{nullptr, {7, 7}}};
            Position FIRST{1, 2}, SECOND{3, 4};
            Positions POSITIONS{{177, 88}};
            MockFallingAnimationFactoryPtr fallingAnimationFactory = std::make_shared<StrictMock<MockFallingAnimationFactory>>();
            MockSwappingAnimationFactoryPtr swappingAnimationFactory = std::make_shared<StrictMock<MockSwappingAnimationFactory>>();
            MockDisappearingAnimationFactoryPtr disappearingAnimationFactory = std::make_shared<StrictMock<MockDisappearingAnimationFactory>>();
            MockAnimationPtr animation = std::make_shared<StrictMock<MockAnimation>>();
            MockAnimationPtr animation2 = std::make_shared<StrictMock<MockAnimation>>();
            StagedBoardAnimator animator{fallingAnimationFactory, swappingAnimationFactory, disappearingAnimationFactory};
            
            void assertDrawAnimation(MockAnimationPtr animation)
            {
                EXPECT_CALL(*animation, drawFrame());
                animator.drawFrame();
            }
            
            void assertUpdateAnimation(MockAnimationPtr animation)
            {
                EXPECT_CALL(*animation, updateFrame());
                animator.updateFrame();
            }
            
            void addAndExpectCreationOfAnimation(MockAnimationPtr animation)
            {
                animator.addFallingAnimation(SPRITES);
                EXPECT_CALL(*fallingAnimationFactory, createFallingAnimation(_, _)).WillOnce(Return(animation)).RetiresOnSaturation();
            }

            void addAnimation(MockAnimationPtr animation)
            {
                animator.addFallingAnimation(SPRITES);
            }
            
            StagedBoardAnimatorTest()
            {
                EXPECT_CALL(*animation, isFinished()).WillRepeatedly(Return(false));
                EXPECT_CALL(*animation2, isFinished()).WillRepeatedly(Return(false));
            }
        };
        
        TEST_F(StagedBoardAnimatorTest, should_add_falling_animations)
        {
            animator.addFallingAnimation(SPRITES);
            
            EXPECT_CALL(*fallingAnimationFactory, createFallingAnimation(SPRITES, NOTHING)).WillOnce(Return(animation));;
            
            animator.updateFrame();
            
            EXPECT_CALL(*fallingAnimationFactory, createFallingAnimation(_, _)).Times(0);
            
            assertDrawAnimation(animation);
        }
        
        TEST_F(StagedBoardAnimatorTest, should_add_swapping_animations)
        {
            animator.addSwappingAnimation(FIRST, SECOND);
            
            EXPECT_CALL(*swappingAnimationFactory, createSwappingAnimation(FIRST, SECOND, NOTHING)).WillOnce(Return(animation));
            
            animator.updateFrame();
            
            EXPECT_CALL(*swappingAnimationFactory, createSwappingAnimation(_, _, _)).Times(0);
            assertDrawAnimation(animation);
        }
        
        TEST_F(StagedBoardAnimatorTest, should_add_disappearing_animations)
        {
            animator.addDisappearingAnimation(POSITIONS);
            
            EXPECT_CALL(*disappearingAnimationFactory, createDisappearingAnimation(POSITIONS, NOTHING)).WillOnce(Return(animation));
            
            animator.updateFrame();
            
            EXPECT_CALL(*disappearingAnimationFactory, createDisappearingAnimation(_, _)).Times(0);
            assertDrawAnimation(animation);
        }
        
        TEST_F(StagedBoardAnimatorTest, should_not_fail_when_updated_empty)
        {
            animator.updateFrame();
        }
        
        TEST_F(StagedBoardAnimatorTest, should_not_fail_when_drawn_empty)
        {
            animator.drawFrame();
        }
        
        TEST_F(StagedBoardAnimatorTest, should_create_next_animation_when_the_previous_one_is_finished_and_pass_the_final_sprites)
        {
            animator.addFallingAnimation(SPRITES);
            animator.addSwappingAnimation(FIRST, SECOND);
            
            EXPECT_CALL(*fallingAnimationFactory, createFallingAnimation(_, _)).WillOnce(Return(animation));
            
            animator.updateFrame();

            EXPECT_CALL(*animation, isFinished()).WillRepeatedly(Return(true));
            EXPECT_CALL(*animation, getFinalSprites()).WillRepeatedly(Return(FINAL_SPRITES));
            EXPECT_CALL(*swappingAnimationFactory, createSwappingAnimation(_, _, FINAL_SPRITES)).WillOnce(Return(animation2));
            
            assertUpdateAnimation(animation);
            
            assertDrawAnimation(animation2);
        }
        
        TEST_F(StagedBoardAnimatorTest, should_not_discard_the_current_animation_when_there_are_no_pending_animations)
        {
            addAndExpectCreationOfAnimation(animation);
            animator.updateFrame();
            
            EXPECT_CALL(*animation, isFinished()).WillRepeatedly(Return(true));
            
            assertUpdateAnimation(animation);
            
            assertDrawAnimation(animation);
        }
        
        TEST_F(StagedBoardAnimatorTest, should_not_discard_the_current_animation_when_it_is_not_finished)
        {
            addAndExpectCreationOfAnimation(animation);
            addAnimation(animation2);
            animator.updateFrame();

            assertUpdateAnimation(animation);
            assertUpdateAnimation(animation);
        }
        
        TEST_F(StagedBoardAnimatorTest, should_finish_when_the_current_animation_finished_and_there_are_no_pending_animations)
        {
            ASSERT_TRUE(animator.isFinished());
            
            addAndExpectCreationOfAnimation(animation);
            
            ASSERT_FALSE(animator.isFinished());
            
            animator.updateFrame();

            ASSERT_FALSE(animator.isFinished());
            
            EXPECT_CALL(*animation, isFinished()).WillRepeatedly(Return(true));
            assertUpdateAnimation(animation);
            
            ASSERT_TRUE(animator.isFinished());
        }
    }
}
