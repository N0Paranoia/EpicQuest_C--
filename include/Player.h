#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include "Tile.h"
#include <iostream>

using namespace std;

class Player
{
    private:
        enum Direction {left, right, up, down};
        const Uint8* keyState;
        int Xvel;
        int Yvel;
        int Speed;
        int frame;
        int StartFrameLeft;
        int EndFrameLeft;
        int StartFrameRight;
        int EndFrameRight;
        int IdleFrameLeft;
        int IdleFrameRight;
        //Render Rect
        SDL_Rect PlayerClips[18];
        bool WalkingLeft;
        bool WalkingRight;

    public:
        //Collision box
        SDL_Rect playerRect;

        Player();
        virtual ~Player();
        //void Event(SDL_Event* event);
        void Input(Tile* tiles[]);
        int LoadMedia(SDL_Renderer* Renderer);
        void Move(Direction dir, Tile* tiles[]);
        void Render(SDL_Renderer* Renderer, SDL_Rect* camera);
        void Cleanup();

    protected:
};

#endif // PLAYER_H
