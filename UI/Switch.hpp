#pragma once
#include "Position.hpp"
#include <memory>
#include <string>

namespace Candies
{
    namespace UI
    {
        class Switch
        {
        public:
            virtual ~Switch() { }
            virtual void disable() = 0;
        };
        
        typedef std::shared_ptr<Switch> SwitchPtr;
    }
}
