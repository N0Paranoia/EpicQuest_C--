#ifndef TILE_H
#define TILE_H

#include <SDL.h>

class Tile
{
    public:
        Tile();
        virtual ~Tile();
        int Init(int x, int y, int TileType);
        int LoadMedia(SDL_Renderer* Renderer, Tile* tiles[]);
        bool SetTiles(Tile* tiles[]);
        int GetType();
        SDL_Rect GetBox();
        void Render(SDL_Renderer* Renderer, SDL_Rect* camera);
    protected:
    private:
    public:
        int Type;
        SDL_Rect TileBox;
        SDL_Rect TileClips[15];
};

#endif // TILE_H
