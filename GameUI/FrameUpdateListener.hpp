#pragma once
#include <memory>

namespace Candies
{
    namespace UI
    {
        class FrameUpdateListener
        {
        public:
            virtual ~FrameUpdateListener() { }
            virtual void update() = 0;
        };
        
        typedef std::shared_ptr<FrameUpdateListener> FrameUpdateListenerPtr;
    }
}
