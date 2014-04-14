#include <UI/StagedBoardAnimator.hpp>
#include "MockFallingAnimationFactory.hpp"
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
            MockFallingAnimationFactoryPtr fallingAnimationFactory = std::make_shared<StrictMock<MockFallingAnimationFactory>>();
            MockAnimationPtr animation = std::make_shared<StrictMock<MockAnimation>>();
            StagedBoardAnimator animator{fallingAnimationFactory};
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
    }
}
