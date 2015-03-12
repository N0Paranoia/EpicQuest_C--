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
    Speed = 1;

}

Player::~Player()
{
    //dtor
}

//void Player::Event(SDL_Event* event)
void Player::Input()
{
    keyState = SDL_GetKeyboardState(NULL);
    if(keyState[SDL_SCANCODE_A])
        this->Move(left);
    if(keyState[SDL_SCANCODE_D])
        this->Move(right);
    if(keyState[SDL_SCANCODE_W])
        this->Move(up);
    if(keyState[SDL_SCANCODE_S])
        this->Move(down);
}

int Player::LoadMedia(SDL_Renderer* Renderer)
{
    //Load Player texture
	/*if((playerTexture.LoadFromFile(Renderer, "assets/player.png")) == NULL)
    {
        cout << "Unable to load Player Texture! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }*/
    if((SpriteSheetTexture.LoadFromFile(Renderer, "assets/spriteSheet48.png")) == NULL)
    {
        cout << "Unable to load Player Texture! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    else
    {
        PlayerClips[0].x = 0;
        PlayerClips[0].y = 0;
        PlayerClips[0].w = 48;
        PlayerClips[0].h = 96;

        PlayerClips[1].x = 48;
        PlayerClips[1].y = 0;
        PlayerClips[1].w = 48;
        PlayerClips[1].h = 96;

        PlayerClips[2].x = 96;
        PlayerClips[2].y = 0;
        PlayerClips[2].w = 48;
        PlayerClips[2].h = 96;

        PlayerClips[3].x = 144;
        PlayerClips[3].y = 0;
        PlayerClips[3].w = 48;
        PlayerClips[3].h = 96;
    }
    return true;
}

void Player::Move(Direction dir)
{
    switch(dir)
    {
    case left:
        cout << "Left" << endl;
        playerX -= Speed;
        break;
    case right:
        cout << "Right" << endl;
        playerX += Speed;
        break;
    case up:
        cout << "Up" << endl;
        playerY -= Speed;
        break;
    case down:
        cout << "Down" << endl;
        playerY += Speed;
        break;
    }
}

void Player::Render(SDL_Renderer* Renderer)
{
    SpriteSheetTexture.Render(Renderer, playerX, playerY, &PlayerClips[3]);
}

void Player::Cleanup()
{

}
