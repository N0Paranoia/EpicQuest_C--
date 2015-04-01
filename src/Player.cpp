#include "Player.h"
#include "Textures.h"
#include "Constants.h"
#include "Collision.h"

//Texture playerTexture;
Textures SpriteSheetTexture;
Collision pCollision;


Player::Player()
{
    playerRect.x = TILE_SIZE    ;
    playerRect.y = 2*TILE_SIZE;
    playerRect.w = TILE_SIZE;
    playerRect.h = 2*TILE_SIZE;
    Xvel = 0;
    Yvel = 0;
    Jvel = 0;
    Speed = 4;
    frame = 0;
    StartFrameLeft = 7;
    EndFrameLeft = 0;
    StartFrameRight = 10;
    EndFrameRight = 17;
    IdleFrameLeft = 8;
    IdleFrameRight = 9;

    jumpSpeed = 60;
    jumpCount = 0;
    jumpHeight = 60;

    WalkingLeft = false;
    WalkingLeft = false;
    isFalling = true;

    climbingSpeed = 8;
    isClimbing = false;

    canJump = true;
    isJumping = false;
}

Player::~Player()
{
    //dtor
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
        PlayerClips[0].x = 0 * playerRect.w;
        PlayerClips[0].y = 0 * playerRect.h;
        PlayerClips[0].w = playerRect.w;
        PlayerClips[0].h = playerRect.h;

        PlayerClips[1].x = 1 * playerRect.w;
        PlayerClips[1].y = 0 * playerRect.h;
        PlayerClips[1].w = playerRect.w;
        PlayerClips[1].h = playerRect.h;

        PlayerClips[2].x = 2 * playerRect.w;
        PlayerClips[2].y = 0 * playerRect.h;
        PlayerClips[2].w = playerRect.w;
        PlayerClips[2].h = playerRect.h;

        PlayerClips[3].x = 3 * playerRect.w;
        PlayerClips[3].y = 0 * playerRect.h;
        PlayerClips[3].w = playerRect.w;
        PlayerClips[3].h = playerRect.h;

        PlayerClips[4].x = 4 * playerRect.w;
        PlayerClips[4].y = 0 * playerRect.h;
        PlayerClips[4].w = playerRect.w;
        PlayerClips[4].h = playerRect.h;

        PlayerClips[5].x = 5 * playerRect.w;
        PlayerClips[5].y = 0 * playerRect.h;
        PlayerClips[5].w = playerRect.w;
        PlayerClips[5].h = playerRect.h;

        PlayerClips[6].x = 6 * playerRect.w;
        PlayerClips[6].y = 0 * playerRect.h;
        PlayerClips[6].w = playerRect.w;
        PlayerClips[6].h = playerRect.h;

        PlayerClips[7].x = 7 * playerRect.w;
        PlayerClips[7].y = 0 * playerRect.h;
        PlayerClips[7].w = playerRect.w;
        PlayerClips[7].h = playerRect.h;

        PlayerClips[8].x = 8 * playerRect.w;
        PlayerClips[8].y = 0 * playerRect.h;
        PlayerClips[8].w = playerRect.w;
        PlayerClips[8].h = playerRect.h;

        PlayerClips[9].x = 9 * playerRect.w;
        PlayerClips[9].y = 0 * playerRect.h;
        PlayerClips[9].w = playerRect.w;
        PlayerClips[9].h = playerRect.h;

        PlayerClips[10].x = 10 * playerRect.w;
        PlayerClips[10].y = 0 * playerRect.h;
        PlayerClips[10].w = playerRect.w;
        PlayerClips[10].h = playerRect.h;

        PlayerClips[11].x = 11 * playerRect.w;
        PlayerClips[11].y = 0 * playerRect.h;
        PlayerClips[11].w = playerRect.w;
        PlayerClips[11].h = playerRect.h;

        PlayerClips[12].x = 12 * playerRect.w;
        PlayerClips[12].y = 0 * playerRect.h;
        PlayerClips[12].w = playerRect.w;
        PlayerClips[12].h = playerRect.h;

        PlayerClips[13].x = 13 * playerRect.w;
        PlayerClips[13].y = 0 * playerRect.h;
        PlayerClips[13].w = playerRect.w;
        PlayerClips[13].h = playerRect.h;

        PlayerClips[14].x = 14 * playerRect.w;
        PlayerClips[14].y = 0 * playerRect.h;
        PlayerClips[14].w = playerRect.w;
        PlayerClips[14].h = playerRect.h;

        PlayerClips[15].x = 15 * playerRect.w;
        PlayerClips[15].y = 0 * playerRect.h;
        PlayerClips[15].w = playerRect.w;
        PlayerClips[15].h = playerRect.h;

        PlayerClips[16].x = 16 * playerRect.w;
        PlayerClips[16].y = 0 * playerRect.h;
        PlayerClips[16].w = playerRect.w;
        PlayerClips[16].h = playerRect.h;

        PlayerClips[17].x = 17 * playerRect.w;
        PlayerClips[17].y = 0 * playerRect.h;
        PlayerClips[17].w = playerRect.w;
        PlayerClips[17].h = playerRect.h;
    }
    return true;
}

void Player::Input(Tile* tiles[])
{
    WalkingLeft = false;
    WalkingRight = false;

    keyState = SDL_GetKeyboardState(NULL);

    if(keyState[SDL_SCANCODE_A])
    {
        Xvel = -Speed;
        this->Move(left, tiles);
        this->Climb(left, tiles);
        WalkingLeft = true;
    }
    if(keyState[SDL_SCANCODE_D])
    {
        Xvel = Speed;
        this->Move(right, tiles);
        this->Climb(right, tiles);
        WalkingRight = true;
    }
    if(keyState[SDL_SCANCODE_W])
    {
        Yvel = -Speed;
        this->Move(up, tiles);
        this->Climb(up, tiles);
    }
    if(keyState[SDL_SCANCODE_S])
    {
        Yvel = Speed;
        this->Move(down, tiles);
        this->Climb(down, tiles);
    }
    if(keyState[SDL_SCANCODE_SPACE])
    {
        this->Jump(tiles);
    }
}

void Player::Jump(Tile* tiles[])
{
    Jvel = -jumpSpeed;
    this->Move(jump, tiles);
}

void Player::Falling(Tile* tiles[])
{
    playerRect.y += GRAVITY;
    isFalling = true;
    if(pCollision.WallCollision(playerRect, tiles) || pCollision.CloudCollision(playerRect, tiles))
    {
        playerRect.y -=GRAVITY;
        isFalling = false;
    }

    //Gravity functions for sloped tiles "y1 = y + (x1 - x)"
    if(pCollision.VarCollision(playerRect, tiles, TILE_SLOPE_LEFT))
    {
        cout << playerRect.y + playerRect.h << endl;
        playerRect.y -=GRAVITY;
        isFalling = false;
    }
    if(pCollision.VarCollision(playerRect, tiles, TILE_SLOPE_RIGHT))
    {
        cout << ((playerRect.y + playerRect.h)%TILE_SIZE)<< endl;
        playerRect.y -=GRAVITY;
        isFalling = false;

    }
}

void Player::Climb(int Dir, Tile* tiles[])
{
    if(pCollision.VarCollision(playerRect, tiles, TILE_LADDER) || pCollision.VarCollision(playerRect, tiles, TILE_LADDER_TOP))
    {
        if(Dir == up)
        {
            isClimbing = true;
            Yvel = -climbingSpeed;
            cout << "ladder up" << endl;
        }
        if(Dir == down)
        {
            isClimbing = true;
            Yvel = climbingSpeed;
            cout << "ladder down" << endl;
        }
        if(Dir == left || Dir == right)
        {
            isClimbing = false;
        }
    }
}

void Player::Move(int Dir, Tile* tiles[])
{
    if(Dir == left || Dir == right)
        playerRect.x += Xvel;
    // Horizontal collision handling
    if(playerRect.x < 0 || playerRect.x + playerRect.w > LEVEL_WIDTH*TILE_SIZE || pCollision.WallCollision(playerRect, tiles))
        playerRect.x -= Xvel;

    if(Dir == up || Dir == down)
        playerRect.y += Yvel;
    // Vertical collision handling
    if(playerRect.y < 0 || playerRect.y + playerRect.h > LEVEL_HEIGHT*TILE_SIZE ||  pCollision.WallCollision(playerRect, tiles))
        playerRect.y -= Yvel;

    if(Dir == jump)
        playerRect.y += Jvel;
    //Jumping collision handeling
    if(playerRect.y < 0 || playerRect.y + playerRect.h > LEVEL_HEIGHT*TILE_SIZE ||  pCollision.WallCollision(playerRect, tiles))
        playerRect.y -= Jvel;
}

void Player::Render(SDL_Renderer* Renderer, SDL_Rect* camera)
{
    // Walking Animation
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
    SpriteSheetTexture.Render(Renderer, playerRect.x - camera->x, playerRect.y - camera->y, &PlayerClips[frame]);
}

void Player::Cleanup()
{
    SpriteSheetTexture.Free();
}
