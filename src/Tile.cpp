#include "Tile.h"
#include "Constants.h"
#include "Texture.h"

Tile::Tile(int x, int y, int Type)
{
    TileBox.x = x;
    TileBox.y = y;
    TileBox.w = TILE_SIZE;
    TileBox.h = TILE_SIZE;

    TileType = Type;
}

Tile::~Tile()
{
    //dtor
}

void Tile::Render()
{

}
