#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>


class Player
{
    private:
        int playerX;
        int playerY;
        int playerWidth;
        int playerHeight;
    public:
        Player();
        virtual ~Player();
        int Test();
        void Render();
    protected:
    private:
};

#endif // PLAYER_H
