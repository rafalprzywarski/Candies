#pragma once
#include <memory>

namespace Candies
{
    namespace UI
    {
        class DrawFrameListener
        {
        public:
            virtual ~DrawFrameListener() { }
            virtual void drawFrame() const = 0;
        };
        
        typedef std::shared_ptr<DrawFrameListener> DrawFrameListenerPtr;
    }
}
