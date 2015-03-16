#ifndef TILES_H
#define TILES_H
#include <SDL.h>


class Tiles
{
    public:
        Tiles(int x, int y, int type);
        virtual ~Tiles();
        int GetType();
        void Render(SDL_Rect& camera);
        //Get collision box
        SDL_Rect GetBox();

    protected:
    private:
        SDL_Rect TileBox;
        int TileType;
};

#endif // TILES_H
