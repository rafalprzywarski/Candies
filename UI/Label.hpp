#pragma once
#include "Position.hpp"
#include <memory>
#include <string>

namespace Candies
{
    namespace UI
    {
        class Label
        {
        public:
            virtual ~Label() { }
            virtual void setText(const std::string& text) = 0;
        };
        
        typedef std::shared_ptr<Label> LabelPtr;
    }
}
