#pragma once
#include <UI/Label.hpp>
#include <gmock/gmock.h>

namespace Candies
{
    namespace UI
    {
        struct MockLabel : Label
        {
            MOCK_METHOD0(update, void());
            MOCK_METHOD1(setText, void(const std::string& text));
        };
        
        typedef std::shared_ptr<MockLabel> MockLabelPtr;
    }
}
