#ifndef WORLD_H
#define WORLD_H

#include <SDL.h>
#include "Constants.h"
#include "Tile.h"
#include "Mobs.h"
#include "Shadows.h"
#include <iostream>

using namespace std;

class World
{
    public:
        World();
        virtual ~World();
        int LoadMedia(SDL_Renderer* Renderer, Tile* tiles[], Mobs* mobs[]);
        bool SetTiles(Tile* tiles[], Mobs* mobs[]);
        bool SetMobs(Mobs* mobs[]);
		bool GenerateShadows(SDL_Rect* source_rect, Shadows* shadows[]);
        void UpdateMobs(Mobs* mobs[], Tile* tiles[], SDL_Rect* playerRect);
        void Render(SDL_Renderer* Renderer, SDL_Rect* camera, Tile* tiles[], Mobs* mobs[], Shadows* shadows[], SDL_Rect* player);
    protected:
    private:
    public:
        SDL_Rect TileClips[TOTAL_TILE_SPRITES];
        SDL_Rect MobClips[TOTAL_MOB_SPRITES];
		SDL_Rect ShadowClips[TOTAL_SHADOW_SPRITES];
        int Type;
        int Type_Mobs;
		int Type_Shadows;
};

#endif // WORLD_H
