#include "Player.h"
#include "Constants.h"

Player::Player()
{
    playerX = 0;
    playerY = 0;
    playerW = TILE_SIZE;
    playerH = TILE_SIZE;
}

Player::~Player()
{
    //dtor
}

void Player::Render()
{
}
