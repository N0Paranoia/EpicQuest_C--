#include "Player.h"
#include "Texture.h"
#include "Constants.h"

//Texture playerTexture;
Texture SpriteSheetTexture;


Player::Player()
{
    playerX = 0;
    playerY = 0;
    playerWidth = TILE_SIZE;
    playerHeight = TILE_SIZE*2;
    Xvel = 0;
    Yvel = 0;
    Speed = 4;
    frame = 0;
    StartFrameLeft = 7;
    EndFrameLeft = 0;
    StartFrameRight = 10;
    EndFrameRight = 17;
    IdleFrameLeft = 8;
    IdleFrameRight = 9;
    WalkingLeft = false;
    WalkingLeft = false;
}

Player::~Player()
{
    //dtor
}

//void Player::Event(SDL_Event* event)
void Player::Input()
{
    WalkingLeft = false;
    WalkingRight = false;

    keyState = SDL_GetKeyboardState(NULL);
    if(keyState[SDL_SCANCODE_A])
    {
        this->Move(left);
        WalkingLeft = true;
    }
    if(keyState[SDL_SCANCODE_D])
    {
        this->Move(right);
        WalkingRight = true;
    }
    if(keyState[SDL_SCANCODE_W])
    {
        this->Move(up);
    }
    if(keyState[SDL_SCANCODE_S])
    {
        this->Move(down);
    }
}

int Player::LoadMedia(SDL_Renderer* Renderer)
{
    //Load Player spritesheet
    if((SpriteSheetTexture.LoadFromFile(Renderer, "assets/spriteSheet48.png")) == NULL)
    {
        cout << "Unable to load Player Texture! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    else
    {
        PlayerClips[0].x = 0 * playerWidth;
        PlayerClips[0].y = 0 * playerHeight;
        PlayerClips[0].w = playerWidth;
        PlayerClips[0].h = playerHeight;

        PlayerClips[1].x = 1 * playerWidth;
        PlayerClips[1].y = 0 * playerHeight;
        PlayerClips[1].w = playerWidth;
        PlayerClips[1].h = playerHeight;

        PlayerClips[2].x = 2 * playerWidth;
        PlayerClips[2].y = 0 * playerHeight;
        PlayerClips[2].w = playerWidth;
        PlayerClips[2].h = playerHeight;

        PlayerClips[3].x = 3 * playerWidth;
        PlayerClips[3].y = 0 * playerHeight;
        PlayerClips[3].w = playerWidth;
        PlayerClips[3].h = playerHeight;

        PlayerClips[4].x = 4 * playerWidth;
        PlayerClips[4].y = 0 * playerHeight;
        PlayerClips[4].w = playerWidth;
        PlayerClips[4].h = playerHeight;

        PlayerClips[5].x = 5 * playerWidth;
        PlayerClips[5].y = 0 * playerHeight;
        PlayerClips[5].w = playerWidth;
        PlayerClips[5].h = playerHeight;

        PlayerClips[6].x = 6 * playerWidth;
        PlayerClips[6].y = 0 * playerHeight;
        PlayerClips[6].w = playerWidth;
        PlayerClips[6].h = playerHeight;

        PlayerClips[7].x = 7 * playerWidth;
        PlayerClips[7].y = 0 * playerHeight;
        PlayerClips[7].w = playerWidth;
        PlayerClips[7].h = playerHeight;

        PlayerClips[8].x = 8 * playerWidth;
        PlayerClips[8].y = 0 * playerHeight;
        PlayerClips[8].w = playerWidth;
        PlayerClips[8].h = playerHeight;

        PlayerClips[9].x = 9 * playerWidth;
        PlayerClips[9].y = 0 * playerHeight;
        PlayerClips[9].w = playerWidth;
        PlayerClips[9].h = playerHeight;

        PlayerClips[10].x = 10 * playerWidth;
        PlayerClips[10].y = 0 * playerHeight;
        PlayerClips[10].w = playerWidth;
        PlayerClips[10].h = playerHeight;

        PlayerClips[11].x = 11 * playerWidth;
        PlayerClips[11].y = 0 * playerHeight;
        PlayerClips[11].w = playerWidth;
        PlayerClips[11].h = playerHeight;

        PlayerClips[12].x = 12 * playerWidth;
        PlayerClips[12].y = 0 * playerHeight;
        PlayerClips[12].w = playerWidth;
        PlayerClips[12].h = playerHeight;

        PlayerClips[13].x = 13 * playerWidth;
        PlayerClips[13].y = 0 * playerHeight;
        PlayerClips[13].w = playerWidth;
        PlayerClips[13].h = playerHeight;

        PlayerClips[14].x = 14 * playerWidth;
        PlayerClips[14].y = 0 * playerHeight;
        PlayerClips[14].w = playerWidth;
        PlayerClips[14].h = playerHeight;

        PlayerClips[15].x = 15 * playerWidth;
        PlayerClips[15].y = 0 * playerHeight;
        PlayerClips[15].w = playerWidth;
        PlayerClips[15].h = playerHeight;

        PlayerClips[16].x = 16 * playerWidth;
        PlayerClips[16].y = 0 * playerHeight;
        PlayerClips[16].w = playerWidth;
        PlayerClips[16].h = playerHeight;

        PlayerClips[17].x = 17 * playerWidth;
        PlayerClips[17].y = 0 * playerHeight;
        PlayerClips[17].w = playerWidth;
        PlayerClips[17].h = playerHeight;
    }
    return true;
}

void Player::Move(Direction dir)
{
    switch(dir)
    {
    case left:
        playerX -= Speed;
        break;
    case right:
        playerX += Speed;
        break;
    case up:
        playerY -= Speed;
        break;
    case down:
        playerY += Speed;
        break;
    }
}

void Player::Render(SDL_Renderer* Renderer)
{
    if(WalkingLeft)
    {
        frame --;
        if(frame < EndFrameLeft)
        {
            frame = StartFrameLeft;
        }
    }
    if(WalkingRight)
    {
        frame ++;
        if(frame  > EndFrameRight)
        {
            frame = StartFrameRight;
        }
    }
    //Render Frame
    SpriteSheetTexture.Render(Renderer, playerX, playerY, &PlayerClips[frame]);
}

void Player::Cleanup()
{

}
