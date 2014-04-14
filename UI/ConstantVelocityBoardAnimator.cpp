#include "ConstantVelocityBoardAnimator.hpp"

namespace Candies
{
    namespace UI
    {
        void ConstantVelocityBoardAnimator::addItems(const SpritesWithPositions& newSprites)
        {
            if (newSprites.empty())
                return;
            startTime = timer->getTime();
            auto lowestHeight = getLowestHeight(newSprites);
            for (auto& s : newSprites)
                sprites.emplace_back(s.sprite, s.position.y - lowestHeight + fallingHeight, s.position);
        }

        void ConstantVelocityBoardAnimator::drawFrame() const
        {
            for (auto& s : sprites)
                s.sprite->drawAt(s.position);
        }

        void ConstantVelocityBoardAnimator::updateFrame()
        {
            auto currentTime = timer->getTime() - startTime;
            for (auto& s : sprites)
                s.position = { s.finalPosition.x, interpolator->interpolate(s.startingHeight, s.finalPosition.y, currentTime) };
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
