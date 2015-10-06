#ifndef AI_H
#define AI_H

#include <SDL.h>
#include "Mobs.h"
#include "Tile.h"

class Ai
{
    public:
        Ai();
        virtual ~Ai();
        int Move(Mobs* mobs[], int i, Tile* tiles[]);
    protected:
    private:
    public:
        bool Left[2] = {false};
        bool Right[2] = {true, true};
};

#endif // AI_H
