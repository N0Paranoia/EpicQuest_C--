#ifndef WORLD_H
#define WORLD_H

#include <SDL.h>
#include "Constants.h"
#include "Tile.h"
#include "Mobs.h"
#include <iostream>

using namespace std;

class World
{
    public:
        World();
        virtual ~World();
        int LoadMedia(SDL_Renderer* Renderer, Tile* tiles[], Mobs* mobs[]);
        bool SetTiles(Tile* tiles[]);
        bool SetMobs(Mobs* mobs[]);
        void UpdateMobs(Mobs* mobs[]);
        void Render(SDL_Renderer* Renderer, SDL_Rect* camera, Tile* tiles[], Mobs* mobs[]);
    protected:
    private:
    public:
        SDL_Rect TileClips[TOTAL_TILE_SPRITES];
        SDL_Rect MobClips[TOTAL_MOB_SPRITES];
        int Type;
};

#endif // WORLD_H
