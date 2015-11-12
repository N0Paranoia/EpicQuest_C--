#ifndef LIGHT_H
#define LIGHT_H

#include <SDL.h>
#include "Constants.h"

class Light
{
    public:
        Light();
        virtual ~Light();
        void Render(SDL_Renderer* Renderer, SDL_Rect* camera);

        SDL_Rect LightSource;
    protected:
    private:

};

#endif // LIGHT_H
