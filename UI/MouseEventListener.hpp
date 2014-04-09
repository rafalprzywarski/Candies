#pragma once
#include "Position.hpp"
#include <memory>

namespace Candies
{
    namespace UI
    {
        class MouseEventListener
        {
        public:
            virtual ~MouseEventListener() { }
            virtual void mouseDown(Position pos) = 0;
        };
        
        typedef std::shared_ptr<MouseEventListener> MouseEventListenerPtr;
    }
}
