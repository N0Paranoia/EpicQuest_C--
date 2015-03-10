#include "EQ.h"

void EQ::Cleanup()
{
    if(Renderer)
    {
        SDL_DestroyRenderer(Renderer);
        Renderer = nullptr;
    }
    if(Texture)
    {
        SDL_DestroyTexture(Texture);
        Texture = nullptr;
    }
    if(Window)
    {
        SDL_DestroyWindow(Window);
        Window = nullptr;
    }


    SDL_Quit();
}
