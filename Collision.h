#ifndef COLLISION_H
#define COLLISION_H
#include "Constants.h"
#include "Tile.h"
#include <SDL.h>


class Collision
{
    public:
        Collision();
        virtual ~Collision();

        //SDL_Rect collisions (ints)
        bool Check_Rect(SDL_Rect a, SDL_Rect b);
        bool CheckCloud_Rect(float timeStep, SDL_Rect a, SDL_Rect b);
    	bool Check_Slope_45_Left_Rect(SDL_Rect a, SDL_Rect b);
    	bool Check_Slope_45_Right_Rect(SDL_Rect a, SDL_Rect b);
        bool Var_Rect(SDL_Rect cBox, Tile* tiles[], int type);
        bool Wall_Rect(SDL_Rect cBox, Tile* tiles[]);
        bool Cloud_Rect(float timeStep, SDL_Rect cBox, Tile* tiles[]);
    	bool Slope_45_Right_Rect(SDL_Rect cBox, Tile* tiles[]);
    	bool Slope_45_Left_Rect(SDL_Rect cBox, Tile* tiles[]);
    	bool Stick_Rect(float timeStep, SDL_Rect cBox, Tile* tiles[]);

        //Box Collisions (floats)
        bool Check_Box(Box a, SDL_Rect b);
        bool CheckCloud_Box(float timeStep, Box a, SDL_Rect b);
        bool Check_Slope_45_Left_Box(Box a, SDL_Rect b);
        bool Check_Slope_45_Right_Box(Box a, SDL_Rect b);
        bool Wall_Box(Box cBox, Tile* tiles[]);
        bool Cloud_Box(float timeStep, Box cBox, Tile* tiles[]);
        bool Var_Box(Box cBox, Tile* tiles[], int type);
        bool Slope_45_Right_Box(Box cBox, Tile* tiles[]);
        bool Slope_45_Left_Box(Box cBox, Tile* tiles[]);

    protected:
    private:
        int i_leftA, i_leftB;
        int i_rightA, i_rightB;
        int i_topA, i_topB;
        int i_bottomA, i_bottomB;
        
        float f_leftA, f_leftB;
        float f_rightA, f_rightB;
        float f_topA, f_topB;
        float f_bottomA, f_bottomB;
};

#endif // COLLISION_H
