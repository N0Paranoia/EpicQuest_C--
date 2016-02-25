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
		isAttacking[i] = false;
    }
	AttackCounter[TOTAL_TILES] = 0;
	AttackDuration = 60;
	AttackDelay = 120;
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

void Ai::Agro(Mobs* mobs[], int i, SDL_Rect* playerRect, int type)
{
    switch(type)
    {
        case MOB_TYPE_1:
        // Check vertical alighnement
        if(playerRect->y > (mobs[i]->getMobBox().y - AGRO_RANGE) && playerRect->y < ((mobs[i]->getMobBox().y + mobs[i]->getMobBox().h) + AGRO_RANGE))
        {
            // Check Horizontal alighnment
            if(playerRect->x + playerRect->w < mobs[i]->getMobBox().x && playerRect->x + playerRect->w > mobs[i]->getMobBox().x - AGRO_RANGE)
            {
                movement[i] = left;
            }
            // Check Horizontal alighnment
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

int Ai::Attack(Mobs* mobs[], int i, SDL_Rect* playerRect, SDL_Rect* shieldRect, int axis)
{
    // Check vertical alighnment
    if(playerRect->y > (mobs[i]->getMobBox().y - ATTACK_RANGE_MELEE) && playerRect->y < ((mobs[i]->getMobBox().y + mobs[i]->getMobBox().h) + ATTACK_RANGE_MELEE))
	{
		//Check horizontal alignment
    	if(playerRect->y > (mobs[i]->getMobBox().y - ATTACK_RANGE_MELEE) && playerRect->y < ((mobs[i]->getMobBox().y + mobs[i]->getMobBox().h) + ATTACK_RANGE_MELEE))
		{
			switch(axis)
			{		
				case X_AXIS:
        		if(playerRect->x <= mobs[i]->getMobBox().x && (playerRect->x + playerRect->w) > mobs[i]->getMobBox().x - ATTACK_RANGE_MELEE)
				{
					if(aiCollision.Check(mobs[i]->getWeaponBox(), *shieldRect)) 
					{
						cout << "shield bounce" << endl;
					}
					else
					{
					}	
					return mobs[i]->getMobBox().x - TILE_SIZE;
				}
				else if((playerRect->x + playerRect->w) >= mobs[i]->getMobBox().x && playerRect->x < (mobs[i]->getMobBox().x + mobs[i]->getMobBox().w) + ATTACK_RANGE_MELEE)
				{
					if(aiCollision.Check(mobs[i]->getWeaponBox(), *shieldRect)) 
					{
						cout << "shield bounce" << endl;
					}
					else
					{
					}
					return mobs[i]->getMobBox().x + TILE_SIZE;
				}
				else
				{
					return -TILE_SIZE;
				}
				break;
	
				case Y_AXIS:
        		if(playerRect->y <= mobs[i]->getMobBox().y && (playerRect->y + playerRect->h) > mobs[i]->getMobBox().y - ATTACK_RANGE_MELEE)
				{
					return mobs[i]->getMobBox().y + ((mobs[i]->getMobBox().h/2)-10);
				}
				else if((playerRect->y + playerRect->h) >= mobs[i]->getMobBox().y && playerRect->y < (mobs[i]->getMobBox().y + mobs[i]->getMobBox().h) + ATTACK_RANGE_MELEE)
				{
					return mobs[i]->getMobBox().y + (mobs[i]->getMobBox().h/2);
				}
				else
				{
					return -TILE_SIZE;
				}
				break;				
			}
		}
		else
		{
			return -TILE_SIZE;
		}
	}
	else
	{
		return -TILE_SIZE;
	}
}

double Ai::Damage(Mobs* mobs[], int i, SDL_Rect* swordRect, int type)
{
    switch(type)
    {
        case MOB_TYPE_1:
        if(aiCollision.Rect(mobs[i]->getMobBox(), *swordRect))
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

int Ai::Move(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect, SDL_Rect* swordRect, SDL_Rect* shieldRect, int type)
{
    //----Basic Wallcollision Ai----(or bounce of shield)----(or sword knockback)----//
    if(aiCollision.Wall(mobs[i]->getMobBox(), tiles) || aiCollision.Rect(mobs[i]->getMobBox(), *swordRect) || aiCollision.Rect(mobs[i]->getMobBox(), *shieldRect))
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

int Ai::UpdateAttack(Mobs* mobs[], SDL_Rect* playerRect, SDL_Rect* shieldRect, int i, int axis)
{	
	switch(axis)
	{
		case X_AXIS:
		return this->Attack(mobs, i, playerRect, shieldRect, X_AXIS);
		break;

		case Y_AXIS:
		return this->Attack(mobs, i, playerRect, shieldRect, Y_AXIS);
		break;
	}
}

int Ai::UpdateMovement(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect, SDL_Rect* swordRect, SDL_Rect* shieldRect, int type, int axis)
{
    //---- Basic Ai "input"----//
    this->Input(i);
    //----Basic Agro Ai----//
    this->Agro(mobs, i, playerRect, type);
    //----Basic Damage taking Ai----//
    this->Damage(mobs, i, swordRect, type);
    //----Basic AI attack ----//
//    this->Attack(mobs, i, playerRect, ShieldBox, type);

    switch(axis)
    {
        case X_AXIS:
        //----Basic Ai Horizontal Movement and collision ----//
        return this->Move(mobs, i, tiles, playerRect, swordRect, shieldRect, type);
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
