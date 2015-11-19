#ifndef SHADOWS_H
#define SHADOWS_H

#include <SDL.h>
#include <iostream>
#include "Textures.h"

using namespace std;

class Shadows
{
    public:
        Shadows(int x, int y, int Type);
 		int getType();
 		SDL_Rect getShadowBox();
        void Update();
 		void Render(Textures* textures, SDL_Rect* clips, SDL_Renderer* Renderer, SDL_Rect* camera);

 		int ShadowType;
 		SDL_Rect ShadowBox;

    protected:
    private:
};


#endif // SHADOWS_H
