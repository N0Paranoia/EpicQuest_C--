#ifndef MOBS_H
#define MOBS_H

#include <SDL.h>
#include <iostream>

using namespace std;

class Mobs
{
    public:
        Mobs(int x, int y, int Type);
 		int getType();
 		SDL_Rect getMobBox();
 		void Render(SDL_Renderer* Renderer, SDL_Rect* camera);
 		
 		int MobType;
 		SDL_Rect MobBox;

    protected:
    private:
};

#endif // MOBS_H