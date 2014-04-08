#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "SDLGameUI.hpp"
#include "SDLEventDispatcher.hpp"
#include <GameRunner/GameRunner.hpp>
#include <GameCore/GameFactory.hpp>
#include "StubItemGenerator.hpp"
#include "StubMouseEventListener.hpp"

int main(int argc, const char * argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG);

    {
        auto ui = std::make_shared<Candies::UI::SDLGameUI>();
        auto mouseEventListener = std::make_shared<Candies::UI::StubMouseEventListener>();
        auto dispatcher = std::make_shared<Candies::UI::SDLEventDispatcher>(ui, mouseEventListener);
        auto itemGenerator = std::make_shared<Candies::GameCore::StubItemGenerator>();
        auto gameLogic = Candies::GameCore::GameFactory().createGame(itemGenerator);
        auto runner = std::make_shared<Candies::GameRunner>(gameLogic, dispatcher);
    
        runner->run();
    }
    
    IMG_Quit();
	SDL_Quit();
}

