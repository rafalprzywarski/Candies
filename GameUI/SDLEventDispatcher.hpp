#pragma once
#include "EventDispatcher.hpp"
#include "SDLGameUI.hpp"

namespace Candies
{
    namespace UI
    {
        class SDLEventDispatcher : public EventDispatcher
        {
        public:
            SDLEventDispatcher(std::shared_ptr<SDLGameUI> ui) : ui(ui) { }
            virtual void dispatch();
            virtual bool isFinished() const;
        private:
            bool finished = false;
            std::shared_ptr<SDLGameUI> ui;
        };
    }
}