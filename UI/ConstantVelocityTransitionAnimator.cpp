#include "ConstantVelocityTransitionAnimator.hpp"
#include <cmath>

namespace Candies
{
    namespace UI
    {
        void ConstantVelocityTransitionAnimator::addTransition(Position first, Position second, SpritePtr sprite)
        {
            position = this->first = first;
            this->second = second;
            this->sprite = sprite;
            startTime = timer->getTime();
        }
        
        void ConstantVelocityTransitionAnimator::updateFrame()
        {
            float elapsedTime = timer->getTime() - startTime;
            float factor = elapsedTime * velocity / distance(first, second);
            position = lerp(first, second, std::min(factor, 1.0f));
        }
        
        void ConstantVelocityTransitionAnimator::drawFrame() const
        {
            if (sprite)
                sprite->drawAt(position);
        }
        
        bool ConstantVelocityTransitionAnimator::isFinished() const
        {
            return false;
        }
        
        int ConstantVelocityTransitionAnimator::lerp(int from, int to, float t)
        {
            return int(std::round(from + (to - from) * t));
        }
        
        float ConstantVelocityTransitionAnimator::distance(Position from, Position to)
        {
            float dx = from.x - to.x, dy = from.y - to.y;
            return std::sqrt(dx * dx + dy * dy);
        }
        
        Position ConstantVelocityTransitionAnimator::lerp(Position from, Position to, float t)
        {
            return {lerp(from.x, to.x, t), lerp(from.y, to.y, t)};
        }

    }
}
