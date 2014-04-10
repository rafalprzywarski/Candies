#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "GameRunnerFactory.hpp"

int main(int argc, const char * argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG);
    TTF_Init();

    try
    {
        auto runner = Candies::GameRunnerFactory().createRunner();
        runner->run();
    }
    catch (std::exception const& e)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Internal error", e.what(), nullptr);
    }
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

