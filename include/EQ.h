#ifndef EQ_H
#define EQ_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EQ
{
    private:
        bool Running;
        SDL_Window* Window;
        SDL_Renderer* Renderer;

    public:
        EQ();
        int Execute();

    public:
        void Event(SDL_Event* Event);
        void Fps();
        bool Init();
        void Loop();
        void Render();
        void Cleanup();
};

#endif // EQ_H
