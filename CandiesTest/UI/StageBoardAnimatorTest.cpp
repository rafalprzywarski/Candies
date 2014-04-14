#include <UI/StagedBoardAnimator.hpp>
#include "MockFallingAnimationFactory.hpp"
#include "MockSwappingAnimationFactory.hpp"
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
            Position FIRST{1, 2}, SECOND{3, 4};
            MockFallingAnimationFactoryPtr fallingAnimationFactory = std::make_shared<StrictMock<MockFallingAnimationFactory>>();
            MockSwappingAnimationFactoryPtr swappingAnimationFactory = std::make_shared<StrictMock<MockSwappingAnimationFactory>>();
            MockAnimationPtr animation = std::make_shared<StrictMock<MockAnimation>>();
            MockAnimationPtr animation2 = std::make_shared<StrictMock<MockAnimation>>();
            StagedBoardAnimator animator{fallingAnimationFactory, swappingAnimationFactory};
            
            void assertDrawAnimation(MockAnimationPtr animation)
            {
                EXPECT_CALL(*animation, drawFrame());
                animator.drawFrame();
            }
            
            void addAndExpectCreationOfAnimation(MockAnimationPtr animation)
            {
                animator.addFallingAnimation(SPRITES);
                EXPECT_CALL(*fallingAnimationFactory, createAnimation(_, _)).WillOnce(Return(animation));
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
            
            EXPECT_CALL(*fallingAnimationFactory, createAnimation(SPRITES, NOTHING)).WillOnce(Return(animation));;
            
            animator.updateFrame();
            
            EXPECT_CALL(*fallingAnimationFactory, createAnimation(_, _)).Times(0);
            
            assertDrawAnimation(animation);
        }
        
        TEST_F(StagedBoardAnimatorTest, should_add_swapping_animations)
        {
            animator.addSwappingAnimation(FIRST, SECOND);
            
            EXPECT_CALL(*swappingAnimationFactory, createAnimation(FIRST, SECOND, NOTHING)).WillOnce(Return(animation));
            
            animator.updateFrame();
            
            EXPECT_CALL(*swappingAnimationFactory, createAnimation(_, _, _)).Times(0);
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
        
        TEST_F(StagedBoardAnimatorTest, should_create_next_animation_when_the_previous_one_is_finished)
        {
            animator.addFallingAnimation(SPRITES);
            animator.addSwappingAnimation(FIRST, SECOND);
            
            EXPECT_CALL(*fallingAnimationFactory, createAnimation(_, _)).WillOnce(Return(animation));
            
            animator.updateFrame();

            EXPECT_CALL(*animation, isFinished()).WillRepeatedly(Return(true));
            EXPECT_CALL(*swappingAnimationFactory, createAnimation(_, _, _)).WillOnce(Return(animation2));
            
            animator.updateFrame();
            
            assertDrawAnimation(animation2);
        }
        
        TEST_F(StagedBoardAnimatorTest, should_not_discard_the_current_animation_when_there_are_no_pending_animations)
        {
            addAndExpectCreationOfAnimation(animation);
            animator.updateFrame();
            
            EXPECT_CALL(*animation, isFinished()).WillRepeatedly(Return(true));
            
            animator.updateFrame();
            
            assertDrawAnimation(animation);
        }
        
        TEST_F(StagedBoardAnimatorTest, should_not_discard_the_current_animation_when_it_is_not_finished)
        {
            addAndExpectCreationOfAnimation(animation);
            addAnimation(animation2);
            
            animator.updateFrame();
            animator.updateFrame();
            animator.updateFrame();
            
            assertDrawAnimation(animation);
            
        }
    }
}
