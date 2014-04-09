#pragma once
#include <Logic/ItemGenerator.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace Logic
    {
        struct MockItemGenerator : ItemGenerator
        {
            MOCK_METHOD0(generate, ItemId());
        };
        
        typedef std::shared_ptr<MockItemGenerator> MockItemGeneratorPtr;
    }
}
