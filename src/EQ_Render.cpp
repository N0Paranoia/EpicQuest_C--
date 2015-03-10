#include "EQ.h"

void EQ::Render()
{
    //Clear screen
    SDL_RenderClear(Renderer);
    //Render texture to screen
    SDL_RenderCopy(Renderer, Texture, NULL, NULL);
    //Update Screen
    SDL_RenderPresent(Renderer);
}
