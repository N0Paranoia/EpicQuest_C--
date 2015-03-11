#include "Player.h"
#include "Texture.h"
#include "Constants.h"

Texture playerTexture;

Player::Player()
{
    playerX = 0;
    playerY = 0;
    playerWidth = TILE_SIZE;
    playerHeight = TILE_SIZE*2;
}

Player::~Player()
{
    //dtor
}

void Player::Event(SDL_Event* event)
{
    if(event->type == SDL_KEYDOWN)
    {
        //Define Player Keyboard inputs
        switch(event->key.keysym.sym)
        {
        case SDLK_a:
            this->Move(left);
            break;
        case SDLK_d:
            this->Move(right);
            break;
        case SDLK_w:
            this->Move(up);
            break;
        case SDLK_s:
            this->Move(down);
            break;
        case SDLK_SPACE:
            cout << "Jump" << endl;
            break;
        }
    }
}

int Player::LoadMedia(SDL_Renderer* Renderer)
{
    //Load Player texture
	if((playerTexture.LoadFromFile(Renderer, "assets/player.png")) == NULL)
    {
        cout << "Unable to load Player Texture! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    return true;
}

void Player::Move(Direction dir)
{
    switch(dir)
    {
    case left:
        cout << "Left" << endl;
        playerX -= 10;
        break;
    case right:
        cout << "Right" << endl;
        playerX += 10;
        break;
    case up:
        cout << "Up" << endl;
        playerY -= 10;
        break;
    case down:
        cout << "Down" << endl;
        playerY += 10;
        break;
    }
}

void Player::Render(SDL_Renderer* Renderer)
{
    playerTexture.Render(Renderer, playerX, playerY);
}

void Player::Cleanup()
{

}
