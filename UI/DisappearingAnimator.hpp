#pragma once
#include "Sprite.hpp"
#include "Position.hpp"
#include <memory>

namespace Candies
{
    namespace UI
    {
        class DisappearingAnimator
        {
        public:
            virtual ~DisappearingAnimator() { }
            virtual void addDisappearing(Position pos, SpritePtr sprite) = 0;
            virtual void updateFrame() = 0;
            virtual void drawFrame() const = 0;
            virtual bool isFinished() const = 0;
        };
        
        typedef std::shared_ptr<DisappearingAnimator> DisappearingAnimatorPtr;
    }
}
