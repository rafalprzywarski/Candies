#include <UI/SmoothSwappingAnimation.hpp>
#include "MockSprite.hpp"
#include <gtest/gtest.h>

using namespace testing;

namespace Candies
{
    namespace UI
    {
        struct SmoothSwappingAnimationTest : Test
        {
            Position FIRST{4, 5}, SECOND{2, 5};
            MockSpritePtr sprite1 = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr sprite2 = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr sprite3 = std::make_shared<StrictMock<MockSprite>>();
            MockSpritePtr sprite4 = std::make_shared<StrictMock<MockSprite>>();

            SpritesWithPositions SPRITES{{sprite1, SECOND}, {sprite2, {6, 6}}, {sprite3, FIRST}, {sprite4, {2, 3}}};
            SpritesWithPositions FINAL_SPRITES{{sprite1, FIRST}, {sprite2, {6, 6}}, {sprite3, SECOND}, {sprite4, {2, 3}}};
        };
        
        TEST_F(SmoothSwappingAnimationTest, should_swap_selected_sprite_positions)
        {
            SmoothSwappingAnimation animation(FIRST, SECOND, SPRITES);
            
            ASSERT_EQ(FINAL_SPRITES, animation.getFinalSprites());
        }
    }
}
