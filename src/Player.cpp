#include "Player.h"
#include "Constants.h"

Player::Player()
{
    playerX = 0;
    playerY = 0;
    playerWidth = TILE_SIZE;
    playerHeight = TILE_SIZE;
}

Player::~Player()
{
    //dtor
}

int Player::Test()
{
    return playerX;
}

void Player::Render()
{
}
