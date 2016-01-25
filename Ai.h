#ifndef AI_H
#define AI_H

#include <SDL.h>
#include "Constants.h"
#include "Mobs.h"
#include "Tile.h"

class Ai
{
    public:
        Ai();
        virtual ~Ai();
        int Input(int i);
        void Agro(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect, int type);
        int Move(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect, SDL_Rect* SwordBox, SDL_Rect* ShieldBox, int type);
     	  int Update(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect, SDL_Rect* SwordBox, SDL_Rect* ShieldBox, int type, int axis);
        int Physics(Mobs* mobs[], int i, Tile* tiles[]);
        int Health(Mobs* mobs[], int i, double damage);
        void Debug();
    protected:
    private:
        SDL_Rect bottomCollisionBox;

        enum Movement
		    {
            idle,
            left,
            right,
        };
        Movement movement[TOTAL_TILES] = {};

		    double health[TOTAL_TILES];
        int Xvel[TOTAL_TILES];
        int Yvel[TOTAL_TILES];

        bool isFalling[TOTAL_TILES];
		    bool isDead[TOTAL_TILES];
};

#endif // AI_H
