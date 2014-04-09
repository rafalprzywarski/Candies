#pragma once
#include <memory>

namespace Candies
{
    namespace UI
    {
        class MouseEventListener
        {
        public:
            virtual ~MouseEventListener() { }
            virtual void mouseDown(int x, int y) = 0;
        };
        
        typedef std::shared_ptr<MouseEventListener> MouseEventListenerPtr;
    }
}
