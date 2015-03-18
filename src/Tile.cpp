#include "Tile.h"
#include "Constants.h"
#include "Texture.h"

//Texture playerTexture;
Texture TileSheetTexture;

Tile::Tile()
{
    TileBox.x = 0;
    TileBox.y = 0;
    TileBox.w = TILE_SIZE;
    TileBox.h = TILE_SIZE;

    TileType = NULL;
}

Tile::~Tile()
{
    //dtor
}

int Tile::LoadMedia(SDL_Renderer* Renderer)
{
        //Load Player spritesheet
    if((TileSheetTexture.LoadFromFile(Renderer, "assets/tileSheet48.png")) == NULL)
    {
        cout << "Unable to load Tile Texture! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    else
    {
        TileClips[CLEAR].x = -TILE_SIZE;
        TileClips[CLEAR].y = -TILE_SIZE;
        TileClips[CLEAR].w = TILE_SIZE;
        TileClips[CLEAR].h = TILE_SIZE;

        TileClips[SKY].x = 0 * TILE_SIZE;
        TileClips[SKY].y = 0 * TILE_SIZE;
        TileClips[SKY].w = TILE_SIZE;
        TileClips[SKY].h = TILE_SIZE;

        TileClips[WALL].x = 1 * TILE_SIZE;
        TileClips[WALL].y = 0 * TILE_SIZE;
        TileClips[WALL].w = TILE_SIZE;
        TileClips[WALL].h = TILE_SIZE;

        TileClips[WOOD].x = 2 * TILE_SIZE;
        TileClips[WOOD].y = 0 * TILE_SIZE;
        TileClips[WOOD].w = TILE_SIZE;
        TileClips[WOOD].h = TILE_SIZE;

        TileClips[DOOR].x = 3 * TILE_SIZE;
        TileClips[DOOR].y = 0 * TILE_SIZE;
        TileClips[DOOR].w = TILE_SIZE;
        TileClips[DOOR].h = TILE_SIZE;

        TileClips[LAVA].x = 0 * TILE_SIZE;
        TileClips[LAVA].y = 1 * TILE_SIZE;
        TileClips[LAVA].w = TILE_SIZE;
        TileClips[LAVA].h = TILE_SIZE;

        TileClips[GRASS].x = 1 * TILE_SIZE;
        TileClips[GRASS].y = 1 * TILE_SIZE;
        TileClips[GRASS].w = TILE_SIZE;
        TileClips[GRASS].h = TILE_SIZE;

        TileClips[WATER].x = 2 * TILE_SIZE;
        TileClips[WATER].y = 1 * TILE_SIZE;
        TileClips[WATER].w = TILE_SIZE;
        TileClips[WATER].h = TILE_SIZE;

        TileClips[PLATFORM].x = 2 * TILE_SIZE;
        TileClips[PLATFORM].y = 2 * TILE_SIZE;
        TileClips[PLATFORM].w = TILE_SIZE;
        TileClips[PLATFORM].h = TILE_SIZE;

        TileClips[LADDER].x = 3 * TILE_SIZE;
        TileClips[LADDER].y = 2 * TILE_SIZE;
        TileClips[LADDER].w = TILE_SIZE;
        TileClips[LADDER].h = TILE_SIZE;

        TileClips[LADDER_TOP].x = 4 * TILE_SIZE;
        TileClips[LADDER_TOP].y = 2 * TILE_SIZE;
        TileClips[LADDER_TOP].w = TILE_SIZE;
        TileClips[LADDER_TOP].h = TILE_SIZE;

        TileClips[SLOPE_RIGHT].x = 0 * TILE_SIZE;
        TileClips[SLOPE_RIGHT].y = 3 * TILE_SIZE;
        TileClips[SLOPE_RIGHT].w = TILE_SIZE;
        TileClips[SLOPE_RIGHT].h = TILE_SIZE;

        TileClips[SLOPE_LEFT].x = 1 * TILE_SIZE;
        TileClips[SLOPE_LEFT].y = 3 * TILE_SIZE;
        TileClips[SLOPE_LEFT].w = TILE_SIZE;
        TileClips[SLOPE_LEFT].h = TILE_SIZE;
    }
}

int Tile::GetType()
{
    return TileType;
}

SDL_Rect Tile::GetBox()
{
    return TileBox;
}

void Tile::Render(SDL_Renderer* Renderer, SDL_Rect* camera)
{
    TileSheetTexture.Render(Renderer, TileBox.x - camera->x, TileBox.y - camera->y, &TileClips[WALL]);
    TileSheetTexture.Render(Renderer, (LEVEL_WIDTH - TILE_SIZE) - camera->x, TileBox.y - camera->y, &TileClips[WALL]);
    TileSheetTexture.Render(Renderer, TileBox.x - camera->x, (LEVEL_HEIGHT - TILE_SIZE) - camera->y, &TileClips[WALL]);
    TileSheetTexture.Render(Renderer, (LEVEL_WIDTH - TILE_SIZE) - camera->x, (LEVEL_HEIGHT - TILE_SIZE) - camera->y, &TileClips[WALL]);
}
