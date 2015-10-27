#ifndef COLLISION_H
#define COLLISION_H
#include "Constants.h"
#include "Tile.h"
#include "Mobs.h"
#include <SDL.h>


class Collision
{
    public:
        Collision();
        virtual ~Collision();
        bool Check(SDL_Rect a, SDL_Rect b);
        bool CheckCloud(SDL_Rect a, SDL_Rect b);
	    bool Check_Slope_45_Left(SDL_Rect a, SDL_Rect b);
        bool Check_Slope_45_Right(SDL_Rect a, SDL_Rect b);
        bool Var(SDL_Rect cBox, Tile* tiles[], int type);
        bool Wall(SDL_Rect cBox, Tile* tiles[]);
        bool Cloud(SDL_Rect cBox, Tile* tiles[]);
        bool Slope_45_Right(SDL_Rect cBox, Tile* tiles[]);
        bool Slope_45_Left(SDL_Rect cBox, Tile* tiles[]);
        bool Stick(SDL_Rect cBox, Tile* tiles[]);
        bool Mob(SDL_Rect cBox, Mobs* mobs[], int type);
    protected:
    private:
        int leftA, leftB;
        int rightA, rightB;
        int topA, topB;
        int bottomA, bottomB;
};

#endif // COLLISION_H
