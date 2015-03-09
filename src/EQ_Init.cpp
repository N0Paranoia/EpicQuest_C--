#include "EQ.h"
#include "Constants.h"

bool EQ::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    if((Window = SDL_CreateWindow("EpicQuest",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
    {
        cout << "Unable to create SDL_Window! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    //Create renderer for window
    if((Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED)) == NULL)
    {
        cout << "Unable to create SDL_Renderer! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    //Initialize renderer color
    SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    //Initialize PNG Loading
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags)& imgFlags))
    {
        cout << "Unable to initialize SDL_Image! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    return true;
}
