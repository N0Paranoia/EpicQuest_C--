#include "EQ.h"

void EQ::Render()
{
    //Clear screen
    SDL_RenderClear(Renderer);
    //Update Screen
    SDL_RenderPresent(Renderer);
}
