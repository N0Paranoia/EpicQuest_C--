#ifndef MOBS_H
#define MOBS_H

#include <SDL.h>
#include <iostream>
#include "Textures.h"

using namespace std;

class Mobs
{
    public:
    Mobs(int x, int y, int Type);
 		int getType();
 		SDL_Rect getMobBox();
    void Update();
 		void Render(Textures* textures, SDL_Rect* clips, SDL_Renderer* Renderer, SDL_Rect* camera, double health);

 		int MobType;
 		SDL_Rect MobBox;
    SDL_Rect HealthBar;

    protected:
    private:
};

#endif // MOBS_H
