#include "EQ.h"
#include "Constants.h"
#include<iostream>

bool EQ::Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    if((Window = SDL_CreateWindow("EpicQuest",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
    {
        std::cout << "Window Creation Error" << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}
