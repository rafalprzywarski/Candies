#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "GameRunnerFactory.hpp"

int main(int argc, const char * argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG);

    try
    {
        auto runner = Candies::GameRunnerFactory().createRunner();
        runner->run();
    }
    catch (std::exception const& e)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Internal error", e.what(), nullptr);
    }
    
    IMG_Quit();
    SDL_Quit();
}

