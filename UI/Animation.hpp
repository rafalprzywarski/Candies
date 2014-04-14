#pragma once
#include <memory>

namespace Candies
{
    namespace UI
    {
        class Animation
        {
        public:
            virtual ~Animation() { }
            virtual void drawFrame() const = 0;
        };
        
        typedef std::shared_ptr<Animation> AnimationPtr;
    }
}
