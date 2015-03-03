#ifndef CAPP_H
#define CAPP_H

#include <SDL.h>

class CApp
{
    private:
        bool Running;

        SDL_Window* Window;

    public:
        CApp();

        int OnExecute();

    public:
        bool OnInit();
        void OnEvent(SDL_Event* Event);
        void OnLoop();
        void OnRender();
        void OnCleanup();
};

#endif // CAPP_H
