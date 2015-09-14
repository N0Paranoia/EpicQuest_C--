#ifndef MOBS_H
#define MOBS_H

#include <SDL.h>

class Mobs
{
    public:
        Mobs(int x, int y, int Type);
 		int getType();
 		SDL_Rect getMobBox();
 		void Render();
 		
 		int MobType;
 		SDL_Rect MobBox;

    protected:
    private:
};

#endif // MOBS_H