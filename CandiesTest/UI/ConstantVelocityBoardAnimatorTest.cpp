#include <UI/ConstantVelocityBoardAnimator.hpp>
#include "MockAnimationTimer.hpp"
#include "MockSprite.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct ConstantVelocityBoardAnimatorTest : Test
        {
            float const CURRENT_TIME = 100;
            int const FALLING_HEIGHT = -40;
            MockSpritePtr sprite1 = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr sprite2 = std::make_shared<StrictMock<MockSprite>>();
            
            MockAnimationTimerPtr timer = std::make_shared<StrictMock<MockAnimationTimer>>();

            ConstantVelocityBoardAnimator animator{timer, FALLING_HEIGHT};
            
            void setElapsedTime(float time)
            {
                EXPECT_CALL(*timer, getTime())
                    .Times(AtMost(1)).WillRepeatedly(Return(CURRENT_TIME + time)).RetiresOnSaturation();
            }
        };
        
        TEST_F(ConstantVelocityBoardAnimatorTest, should_put_the_lowest_item_at_falling_height_when_adding_items)
        {
            Position POS1{10, 13}, POS2{10, 17};
            setElapsedTime(0);
            animator.addItems({{sprite1, POS1}, {sprite2, POS2}});
            
            Position FALLING_POS1{POS1.x, POS1.y - POS2.y + FALLING_HEIGHT}, FALLING_POS2{POS2.x, FALLING_HEIGHT};
            EXPECT_CALL(*sprite1, drawAt(FALLING_POS1));
            EXPECT_CALL(*sprite2, drawAt(FALLING_POS2));
            
            animator.drawFrame();
        }
        
        TEST_F(ConstantVelocityBoardAnimatorTest, should_do_nothing_when_adding_an_empty_collection)
        {
            animator.addItems({});
        }
    }
}
