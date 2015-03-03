#include "EQ.h"

void EQ::Cleanup()
{
    if(Window)
    {
        SDL_DestroyWindow(Window);
        Window = NULL;
    }
    SDL_Quit();
}
