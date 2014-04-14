#include "SmoothDisappearingAnimation.hpp"
#include <unordered_set>

namespace Candies
{
    namespace UI
    {
        SmoothDisappearingAnimation::SmoothDisappearingAnimation(DisappearingAnimatorPtr disappearingAnimator, const Positions& toRemove, const SpritesWithPositions& oldSprites)
        : disappearingAnimator(disappearingAnimator)
        {
            std::unordered_set<Position> blackList{toRemove.begin(), toRemove.end()};
            for (auto& s : oldSprites)
                if (blackList.count(s.position))
                    disappearingAnimator->addDisappearing(s.position, s.sprite);
                else
                    finalSprites.push_back(s);
        }
        
        SpritesWithPositions SmoothDisappearingAnimation::getFinalSprites() const
        {
            return finalSprites;
        }
        
        void SmoothDisappearingAnimation::updateFrame()
        {
            disappearingAnimator->updateFrame();
        }
        
        void SmoothDisappearingAnimation::drawFrame() const
        {
            disappearingAnimator->drawFrame();
            for (auto& s : finalSprites)
                s.sprite->drawAt(s.position);
        }
        
        bool SmoothDisappearingAnimation::isFinished() const
        {
            return disappearingAnimator->isFinished();
        }
        
    }
}
