#include "Tiles.h"
#include "Constants.h"

Tiles::Tiles(int x, int y, int type)
{
    TileBox.x = x;
    TileBox.y = y;
    TileBox.w = TILE_SIZE;
    TileBox.h = TILE_SIZE;

    TileType = type;
}

Tiles::~Tiles()
{
    //dtor
}

int Tiles::GetType()
{
    return TileType;
}

SDL_Rect Tiles::GetBox()
{
    return TileBox;
}
