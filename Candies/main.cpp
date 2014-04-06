#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <memory>
#include <iostream>
#include "ResourcePath.h"

int main(int argc, const char * argv[])
{
    auto SCREEN_WIDTH = 755, SCREEN_HEIGHT = 600;
    
	SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG);
    std::shared_ptr<SDL_Window> window(SDL_CreateWindow("Candies", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN), SDL_DestroyWindow);
    std::shared_ptr<SDL_Renderer> renderer(SDL_CreateRenderer(&*window, -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
    
    std::shared_ptr<SDL_Texture> background(IMG_LoadTexture(&*renderer, getResourcePath("BackGround.jpg").c_str()), SDL_DestroyTexture);
    
    auto done = false;
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
                done = true;
        SDL_RenderClear(&*renderer);
        SDL_RenderCopy(&*renderer, &*background, nullptr, nullptr);
        SDL_RenderPresent(&*renderer);
    }
    
    IMG_Quit();
	SDL_Quit();
}

