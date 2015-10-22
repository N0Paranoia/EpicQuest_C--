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
        int Move(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect, int type);
        int Update(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect, int type, int axis);
        int Fall(Mobs* mobs[], int i, Tile* tiles[]);
        void Debug();
    protected:
    private:

        enum Movement
        {
                idle,
                left,
                right,
        };
        Movement movement[TOTAL_TILES] = {};

        int Xvel[TOTAL_TILES];
        int Yvel[TOTAL_TILES];

        bool isFalling[TOTAL_TILES];
};

#endif // AI_H
