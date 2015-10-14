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
        int Agro(Mobs* mobs[], int i, Tile* tiles[]);
        int Update(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect);
        int Fall(Mobs* mobs[], int i, Tile* tiles[]);
        void Debug();
    protected:
    private:
        bool Left[TOTAL_TILES];
        bool Right[TOTAL_TILES];
        // bool Falling[TOTAL_MOBS];
};

#endif // AI_H
