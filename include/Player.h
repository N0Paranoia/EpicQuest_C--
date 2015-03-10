#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>


class Player
{
    private:
        int playerX;
        int playerY;
        int playerW;
        int playerH;
    public:
        Player();
        virtual ~Player();
        void Render();
    protected:
    private:
};

#endif // PLAYER_H
