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
    bool SetTiles(Tile* tiles[], Mobs* mobs[]);
    bool SetMobs(Mobs* mobs[]);
    void UpdateMobs(Mobs* mobs[], Tile* tiles[], SDL_Rect* playerRect, SDL_Rect* SwordBox, SDL_Rect* ShieldBox);
    void Render(SDL_Renderer* Renderer, SDL_Rect* camera, Tile* tiles[], Mobs* mobs[], SDL_Rect* player, SDL_Rect* SwordBox);
protected:
private:
public:
    SDL_Rect TileClips[TOTAL_TILE_SPRITES];
    SDL_Rect MobClips[TOTAL_MOB_SPRITES];
    SDL_Rect ShadowClips[TOTAL_SHADOW_SPRITES];
    SDL_Rect HealthBar[TOTAL_TILES];
    int Type;
    int Type_Mobs;
    int Type_Shadows;
};

#endif // WORLD_H
