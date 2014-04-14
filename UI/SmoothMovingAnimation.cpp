#include "SmoothMovingAnimation.hpp"

namespace Candies
{
    namespace UI
    {
        SmoothMovingAnimation::SmoothMovingAnimation(TransitionAnimatorPtr transitionAnimator, const SpriteMovements& movements, const SpritesWithPositions& oldSprites)
        : transitionAnimator(transitionAnimator)
        {
            auto transitions = createMovementTransitions(movements);
            addTransitions(transitions, oldSprites);
        }
        
        SpritesWithPositions SmoothMovingAnimation::getFinalSprites() const
        {
            auto finalSprites = staticSprites;
            finalSprites.insert(finalSprites.end(), movingSprites.begin(), movingSprites.end());
            return finalSprites;
        }
        
        void SmoothMovingAnimation::updateFrame()
        {
            transitionAnimator->updateFrame();
        }
        
        void SmoothMovingAnimation::drawFrame() const
        {
            transitionAnimator->drawFrame();
            for (auto& s : staticSprites)
                s.sprite->drawAt(s.position);
        }
        
        bool SmoothMovingAnimation::isFinished() const
        {
            return transitionAnimator->isFinished();
        }
        
        SmoothMovingAnimation::Transitions SmoothMovingAnimation::createMovementTransitions(const SpriteMovements& movements)
        {
            std::unordered_map<Position, Position> transitions;
            for (auto& m : movements)
                transitions.emplace(m.from, m.to);
            return std::move(transitions);
        }
        
        void SmoothMovingAnimation::addTransitions(const Transitions& transitions, const SpritesWithPositions& oldSprites)
        {
            for (auto const& s : oldSprites)
            {
                auto transition = transitions.find(s.position);
                if (transition == transitions.end())
                {
                    staticSprites.push_back(s);
                    continue;
                }
                transitionAnimator->addTransition(s.position, transition->second, s.sprite);
                movingSprites.emplace_back(s.sprite, transition->second);
            }
        }
    }
}
