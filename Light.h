#ifndef LIGHT_H
#define LIGHT_H

#include <SDL.h>
#include "Constants.h"

class Light
{
    private:
        SDL_Rect cube[1];

    public:
        Light();
        virtual ~Light();
        int LoadMedia(SDL_Renderer* Renderer);
        void Render(SDL_Renderer* Renderer, SDL_Rect* camera);
        void Cleanup();

    protected:

};

#endif // LIGHT_H
