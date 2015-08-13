#include "Physics.h"
#include "Collision.h"
#include "Constants.h"

Collision PhCollision;

Physics::Physics()
{
}

Physics::~Physics()
{
}

bool Physics::Gravity_Rect(SDL_Rect a, Tile* tiles[])
{
	if(PhCollision.Wall_Rect(a, tiles) ||
			PhCollision.Cloud_Rect(a, tiles) ||
			PhCollision.Slope_45_Left_Rect(a, tiles) ||
			PhCollision.Slope_45_Right_Rect(a, tiles)
	  )
	{
		return true;
	}
	return false;
}

bool Physics::Gravity_Box(Box a, Tile* tiles[])
{
	if(PhCollision.Wall_Box(a, tiles) ||
			PhCollision.Cloud_Box(a, tiles) ||
			PhCollision.Slope_45_Left_Box(a, tiles) ||
			PhCollision.Slope_45_Right_Box(a, tiles)
	  )
	{
		return true;
	}
	return false;
}

int Physics::StickToFloor_Rect(SDL_Rect a, SDL_Rect b, Tile* tiles[])
{
	// Correct if object is floating due (fast) collision
	if(PhCollision.Var_Rect(b, tiles, TILE_SLOPE_LEFT))
	{
		if((TILE_SIZE - ((a.x) + (a.w-1)) % TILE_SIZE) == 1)
		{
			// compesate for colliding in to next tile becoude of the a.w -1
			return ((a.y)/ TILE_SIZE)*TILE_SIZE;
		}
		return (TILE_SIZE - ((a.x) + (a.w-1)) % TILE_SIZE) + ((a.y)/ TILE_SIZE)*TILE_SIZE;
	}	
	else if(PhCollision.Var_Rect(b, tiles, TILE_SLOPE_RIGHT))
	{
		return ((a.x) % TILE_SIZE) + ((a.y)/ TILE_SIZE)*TILE_SIZE;
	}
	else	
	{
		return (((a.y + a.h+(TILE_SIZE/4))/TILE_SIZE) * TILE_SIZE) - a.h;
	}
}

int Physics::StickToFloor_Box(Box a, SDL_Rect b, Tile* tiles[])
{
	// Correct if object is floating due (fast) collision
	if(PhCollision.Var_Rect(b, tiles, TILE_SLOPE_LEFT))
	{
		if((TILE_SIZE - (((int)a.x) + ((int)a.w-1)) % TILE_SIZE) == 1)
		{
			// compesate for colliding in to next tile becoude of the a.w -1
			return (((int)a.y)/ TILE_SIZE)*TILE_SIZE;
		}
		return (TILE_SIZE - (((int)a.x) + ((int)a.w-1)) % TILE_SIZE) + (((int)a.y)/ TILE_SIZE)*TILE_SIZE;
	}	
	else if(PhCollision.Var_Rect(b, tiles, TILE_SLOPE_RIGHT))
	{
		return (((int)a.x) % TILE_SIZE) + (((int)a.y)/ TILE_SIZE)*TILE_SIZE;
	}
	else	
	{
		return ((((int)a.y + (int)a.h+(TILE_SIZE/4))/TILE_SIZE) * TILE_SIZE) - a.h;
	}
}
