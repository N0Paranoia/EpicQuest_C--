#ifndef TILE_H
#define TILE_H

#include <SDL.h>

class Tile
{
    public:
        Tile(int x, int y, int Type);
        virtual ~Tile();
        void Render();
    protected:
    private:
    public:
        int TileType;
        SDL_Rect TileBox;
};

#endif // TILE_H
