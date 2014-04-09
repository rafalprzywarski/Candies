#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "GameRunnerFactory.hpp"

int main(int argc, const char * argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG);

    {
        auto runner = Candies::GameRunnerFactory().createRunner();
        runner->run();
    }
    
    IMG_Quit();
    SDL_Quit();
}

