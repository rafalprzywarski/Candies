#pragma once
#include "Sprite.hpp"
#include "DrawFrameListener.hpp"
#include <memory>

namespace Candies
{
    namespace UI
    {
        class Background : public DrawFrameListener
        {
        public:
            Background(SpritePtr sprite) : sprite(std::move(sprite)) { }
            void drawFrame() const;
        private:
            SpritePtr sprite;
        };
    }
}
