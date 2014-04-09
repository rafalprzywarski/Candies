#pragma once
#include <memory>

namespace Candies
{
    namespace UI
    {
        class EventDispatcher
        {
        public:
            virtual ~EventDispatcher() { }
            virtual void dispatch() = 0;
            virtual bool isFinished() const = 0;
        };
        
        typedef std::shared_ptr<EventDispatcher> EventDispatcherPtr;
    }
}
