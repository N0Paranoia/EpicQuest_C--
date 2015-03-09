#include "EQ.h"


void EQ::Event(SDL_Event* Event)
{
    if(Event->type == SDL_QUIT)
    {
        Running = false;
    }
    else if(Event->type == SDL_KEYDOWN)
    {
        //Define Keyboard inputs
        switch(Event->key.keysym.sym)
        {
        case SDLK_q:
            cout << "Quit" << endl;
            Running = false;
            break;
        case SDLK_a:
            cout << "Left" << endl;
            break;
        case SDLK_d:
            cout << "Right" << endl;
            break;
        case SDLK_w:
            cout << "Up" << endl;
            break;
        case SDLK_s:
            cout << "Down" << endl;
            break;
        case SDLK_SPACE:
            cout << "Jump" << endl;
            break;
        }
    }
}
