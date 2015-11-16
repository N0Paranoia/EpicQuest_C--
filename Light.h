#ifndef LIGHT_H
#define LIGHT_H

#include <SDL.h>
#include "Constants.h"

class Light
{
    private:
        SDL_Rect cube[TOTAL_TILES];

    public:
        Light();
        virtual ~Light();
        int LoadMedia(SDL_Renderer* Renderer);
        void InitShadows(int locationX,int locationY);
        int DrawShadows(int locationX,int locationY, SDL_Rect cube);
        void Render(SDL_Renderer* Renderer, SDL_Rect* camera);
        void Cleanup();

    protected:

};

#endif // LIGHT_H
