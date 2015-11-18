#ifndef LIGHT_H
#define LIGHT_H

#include <SDL.h>
#include "Constants.h"
#include "Textures.h"

class Light
{
    public:
        Light(int x, int y);
        virtual ~Light();
        void Render(Textures* textures, SDL_Rect* clips, SDL_Renderer* Renderer, SDL_Rect* camera);
        void Cleanup();

		SDL_Rect ShadowBox;
    protected:

};

#endif // LIGHT_H
