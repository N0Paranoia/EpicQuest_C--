#include "CApp.h"

void CApp::OnCleanup()
{
    if(Window)
    {
        SDL_DestroyWindow(Window);
        Window = NULL;
    }
    SDL_Quit();
}
