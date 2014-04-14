#include "ConstantVelocityBoardAnimator.hpp"

namespace Candies
{
    namespace UI
    {
        void ConstantVelocityBoardAnimator::addItems(const SpritesWithPositions& newSprites)
        {
            auto lowestHeight = getLowestHeight(newSprites);
            for (auto& s : newSprites)
                sprites.push_back(SpriteWithPosition(s.sprite, {s.position.x, s.position.y - lowestHeight + fallingHeight}));
        }

        void ConstantVelocityBoardAnimator::drawFrame() const
        {
            for (auto& s : sprites)
                s.sprite->drawAt(s.position);
        }
        
        int ConstantVelocityBoardAnimator::getLowestHeight(const SpritesWithPositions& sprites)
        {
            return std::min_element(
                sprites.begin(), sprites.end(),
                [](const SpriteWithPosition& left, const SpriteWithPosition& right)
                {
                    return left.position.y > right.position.y;
                })->position.y;
        }

    }
}
