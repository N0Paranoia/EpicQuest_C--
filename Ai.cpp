#include "Ai.h"
#include "Constants.h"
#include "Collision.h"
#include "Physics.h"

Collision aiCollision;
Physics aiPhysics;

Ai::Ai()
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        isFalling[i] = true;
        health[i] = 100;
    }
}

Ai::~Ai()
{
    //dtor
}

int Ai::Input(int i)
{
    if(movement[i] == left)
    {
        return -4;
    }
    if(movement[i] == right)
    {
        return 4;
    }
    if(movement[i] == idle)
    {
        return 0;
    }
    return 0;
}

void Ai::Agro(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect, int type)
{
    switch(type)
    {
        case MOB_TYPE_1:
        if(playerRect->y > (mobs[i]->getMobBox().y - AGRO_RANGE) && playerRect->y < ((mobs[i]->getMobBox().y + mobs[i]->getMobBox().h) + AGRO_RANGE))
        {
            if(playerRect->x + playerRect->w < mobs[i]->getMobBox().x && playerRect->x + playerRect->w > mobs[i]->getMobBox().x - AGRO_RANGE)
            {
                movement[i] = left;
            }
            else if(playerRect->x > (mobs[i]->getMobBox().x + mobs[i]->getMobBox().w) && playerRect->x < (mobs[i]->getMobBox().x + mobs[i]->getMobBox().w) + AGRO_RANGE)
            {
                movement[i] = right;
            }
            else
            {
                movement[i] = idle;
            }
        }
        break;
    }
}

double Ai::Damage(Mobs* mobs[], int i, SDL_Rect* SwordBox, int type)
{
    switch(type)
    {
        case MOB_TYPE_1:
        if(aiCollision.Rect(mobs[i]->getMobBox(), *SwordBox))
        {
            return 10;
        }
        break;
    }
    return 0;
}

int Ai::Physics(Mobs* mobs[], int i, Tile* tiles[])
{
    bottomCollisionBox = { mobs[i]->getMobBox().x, (mobs[i]->getMobBox().y +  mobs[i]->getMobBox().h),  mobs[i]->getMobBox().w, 1};

    if(!aiCollision.Stick(bottomCollisionBox, tiles))
    {
        return aiPhysics.StickToFloor( mobs[i]->getMobBox(), bottomCollisionBox, tiles);
    }
    else if(aiCollision.Slope_45_Left(mobs[i]->getMobBox(), tiles))//[/]
    {
        // compesate for colliding in to next tile becoude of the playerRect.w -1
        return ((TILE_SIZE - ((mobs[i]->getMobBox().x) + (mobs[i]->getMobBox().w-1)) % TILE_SIZE) + ((mobs[i]->getMobBox().y-1)/ TILE_SIZE)*TILE_SIZE) -1;
    }
    else if(aiCollision.Slope_45_Right(mobs[i]->getMobBox(), tiles))//[/])
    {
        return ((mobs[i]->getMobBox().x) % TILE_SIZE) + ((mobs[i]->getMobBox().y-1)/ TILE_SIZE)*TILE_SIZE;
    }
    return mobs[i]->getMobBox().y;
}

int Ai::Health(int i, double damage)
{
    // isDead[i] = false;
    health[i] = (health[i] - damage);
    return health[i];
}

bool Ai::Alive(int i)
{
    if(this->Health(i, 0) > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Ai::Move(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect, SDL_Rect* SwordBox, SDL_Rect* ShieldBox, int type)
{
    //----Basic Wallcollision Ai----(or bounce of shield)----(or sword knockback)----//
    if(aiCollision.Wall(mobs[i]->getMobBox(), tiles) || aiCollision.Rect(mobs[i]->getMobBox(), *SwordBox) || aiCollision.Rect(mobs[i]->getMobBox(), *ShieldBox))
    {
        if(movement[i] == left)
        {
            movement[i] = right;
        }
        else if(movement[i] == right)
        {
            movement[i] = left;
        }
    }
    //----Basic Wallcollision Ai----//
    return mobs[i]->getMobBox().x + this->Input(i);
}

int Ai::Update(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect, SDL_Rect* SwordBox, SDL_Rect* ShieldBox, int type, int axis)
{
    //---- Basic Ai "input"----//
    this->Input(i);
    //----Basic Agro Ai----//
    this->Agro(mobs, i, tiles, playerRect, type);
    //----Basix Damage taking Ai----//
    this->Damage(mobs, i, SwordBox, type);

    switch(axis)
    {
        case X_AXIS:
        //----Basic Ai Horizontal Movement and collision ----//
        return this->Move(mobs, i, tiles, playerRect, SwordBox, ShieldBox, type);
        break;

        case Y_AXIS:
        return this->Physics(mobs, i, tiles);
        break;
    }
    return 0;
}

void Ai::Debug()
{
    cout << "Debug!" << endl;
}
