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
            StagedBoardAnimator animator{fallingAnimationFactory, swappingAnimationFactory};
        };
        
        TEST_F(StagedBoardAnimatorTest, should_add_falling_animations)
        {
            animator.addFallingAnimation(SPRITES);
            
            EXPECT_CALL(*fallingAnimationFactory, createAnimation(SPRITES, NOTHING)).WillOnce(Return(animation));;
            
            animator.updateFrame();
            
            EXPECT_CALL(*fallingAnimationFactory, createAnimation(_, _)).Times(0);
            EXPECT_CALL(*animation, drawFrame());
            
            animator.drawFrame();
        }
        
        TEST_F(StagedBoardAnimatorTest, should_add_swapping_animations)
        {
            animator.addSwappingAnimation(FIRST, SECOND);
            
            EXPECT_CALL(*swappingAnimationFactory, createAnimation(FIRST, SECOND, NOTHING)).WillOnce(Return(animation));
            
            animator.updateFrame();
            
            EXPECT_CALL(*swappingAnimationFactory, createAnimation(_, _, _)).Times(0);
            EXPECT_CALL(*animation, drawFrame());
            
            animator.drawFrame();
        }
        
        TEST_F(StagedBoardAnimatorTest, should_not_fail_when_updated_empty)
        {
            animator.updateFrame();
        }
    }
}
