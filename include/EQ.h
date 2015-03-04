#ifndef CAPP_H
#define CAPP_H

#include <SDL.h>

class EQ
{
    private:
        bool Running;
        SDL_Window* Window;

    public:
        EQ();
        int Execute();

    public:
        bool Init();
        void OnEvent(SDL_Event* Event);
        void Loop();
        void Render();
        void Cleanup();
};

#endif // CAPP_H
