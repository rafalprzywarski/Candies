#pragma once
#include "ItemGenerator.hpp"
#include <chrono>
#include <random>

namespace Candies
{
    namespace Logic
    {
        class StdItemGenerator : public ItemGenerator
        {
        public:
            StdItemGenerator(int count)
            : generator(unsigned(std::chrono::system_clock::now().time_since_epoch().count())), distribution(0, count - 1) { }
            ItemId generate() { return distribution(generator); }
        private:
            std::default_random_engine generator;
            std::uniform_int_distribution<int> distribution;
        };
    }
}
