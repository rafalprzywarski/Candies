#pragma once
#include <GameCore/ItemGenerator.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace GameCore
    {
        struct MockItemGenerator : ItemGenerator
        {
            MOCK_METHOD0(generate, ItemId());
        };
        
        typedef std::shared_ptr<MockItemGenerator> MockItemGeneratorPtr;
    }
}
