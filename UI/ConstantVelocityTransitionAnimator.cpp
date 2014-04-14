#include "ConstantVelocityTransitionAnimator.hpp"
#include <cmath>

namespace Candies
{
    namespace UI
    {
        void ConstantVelocityTransitionAnimator::addTransition(Position first, Position second, SpritePtr sprite)
        {
            transitions.emplace_back(first, second, timer->getTime(), sprite);
        }
        
        void ConstantVelocityTransitionAnimator::updateFrame()
        {
            auto time = timer->getTime();
            for (auto& t : transitions)
                t.update(time, velocity);
        }
        
        void ConstantVelocityTransitionAnimator::drawFrame() const
        {
            for (auto& t : transitions)
                t.draw();
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

        void ConstantVelocityTransitionAnimator::Transition::update(float time, float velocity)
        {
            float elapsedTime = time - startTime;
            float factor = elapsedTime * velocity / distance(first, second);
            position = lerp(first, second, std::min(factor, 1.0f));
        }
        
        void ConstantVelocityTransitionAnimator::Transition::draw() const
        {
            sprite->drawAt(position);
        }
    }
}
