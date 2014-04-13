#pragma once
#include <memory>

namespace Candies
{
    namespace UI
    {
        class UpdateFrameListener
        {
        public:
            virtual ~UpdateFrameListener() { }
            virtual void updateFrame() = 0;
        };
        
        typedef std::shared_ptr<UpdateFrameListener> UpdateFrameListenerPtr;
    }
}
