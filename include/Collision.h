#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>


class Collision
{
    public:
        Collision();
        virtual ~Collision();
        bool CheckCollision(SDL_Rect a, SDL_Rect b);
    protected:
    private:
        int leftA, leftB;
        int rightA, rightB;
        int topA, topB;
        int bottomA, bottomB;
};

#endif // COLLISION_H
