#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

using namespace std;

class Player
{
    private:
        int playerWidth;
        int playerHeight;
        enum Direction {left, right, up, down};

    public:
        int playerX;
        int playerY;

        Player();
        virtual ~Player();
        void Event(SDL_Event* event);
        int LoadMedia(SDL_Renderer* Renderer);
        void Move(Direction dir);
        void Render(SDL_Renderer* Renderer);
        void Cleanup();

    protected:
};

#endif // PLAYER_H
