#include "EQ.h"
#include<iostream>

void EQ::Event(SDL_Event* Event)
{
    if(Event->type == SDL_QUIT)
    {
        Running = false;
    }
    else if(Event->type == SDL_KEYDOWN)
    {
        switch(Event->key.keysym.sym)
        {
        case SDLK_a:
            std::cout << "Left" << std::endl;
            break;
        case SDLK_d:
            std::cout << "Right" << std::endl;
            break;
        case SDLK_w:
            std::cout << "Up" << std::endl;
            break;
        case SDLK_s:
            std::cout << "Down" << std::endl;
            break;
        }
    }
}
