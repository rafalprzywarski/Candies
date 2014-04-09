#pragma once
#include "ItemId.hpp"
#include <memory>

namespace Candies
{
    namespace Logic
    {
        class ItemGenerator
        {
        public:
            virtual ~ItemGenerator() { }
            virtual ItemId generate() = 0;
        };
    
        typedef std::shared_ptr<ItemGenerator> ItemGeneratorPtr;
    }
}
