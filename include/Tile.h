#ifndef TILE_H
#define TILE_H
#include <SDL.h>


class Tile
{
    public:
        Tile();
        virtual ~Tile();
        int GetType();
        int LoadMedia(SDL_Renderer* Renderer, Tile* tiles[]);
        void Render(SDL_Renderer* Renderer, SDL_Rect* camera);
        bool SetTiles(Tile* tiles[]);
        //Get collision box
        SDL_Rect GetBox();

    protected:
    private:
        SDL_Rect TileBox;
        SDL_Rect TileClips[15];
        int TileType;
};

#endif // TILES_H
