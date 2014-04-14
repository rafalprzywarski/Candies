#include "ConstantTimeDisappearingAnimator.hpp"

namespace Candies
{
    namespace UI
    {
        ConstantTimeDisappearingAnimator::ConstantTimeDisappearingAnimator(AnimationTimerPtr timer, float animationTime)
        : timer(timer), animationTime(animationTime), startTime(timer->getTime()), currentTime(startTime)
        {
            
        }

        void ConstantTimeDisappearingAnimator::addDisappearing(Position pos, SpritePtr sprite)
        {
            sprites.emplace_back(sprite, pos);
        }
        
        void ConstantTimeDisappearingAnimator::updateFrame()
        {
            currentTime = timer->getTime();
        }
        
        void ConstantTimeDisappearingAnimator::drawFrame() const
        {
            auto alpha = calculateAlpha();
            for (auto& s : sprites)
                s.sprite->drawWithAlphaAt(alpha, s.position);
        }
        
        bool ConstantTimeDisappearingAnimator::isFinished() const
        {
            return currentTime >= (startTime + animationTime);
        }
        
        float ConstantTimeDisappearingAnimator::calculateAlpha() const
        {
            auto time = timer->getTime();
            return std::max(0.0f, 1 - ((time - startTime) / animationTime));
        }
    }
}
