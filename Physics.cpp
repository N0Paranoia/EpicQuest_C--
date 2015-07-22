#include "Physics.h"
#include "Collision.h"

Collision PhCollision;

Physics::Physics()
{
}

Physics::~Physics()
{
}

bool Physics::Gravity(SDL_Rect a, Tile* tiles[])
{
	if(PhCollision.Wall(a, tiles) ||
			PhCollision.Cloud(a, tiles) ||
			PhCollision.Slope_45_Left(a, tiles) ||
			PhCollision.Slope_45_Right(a, tiles)
	  )
	{
		return true;
	}
	return false;
}

int Physics::StickToFloor(SDL_Rect a, Tile* tiles[])
{
	// Correct if object is floating due (fast) collision
 	// Using Var collision i.s.o. Sloped collision becaus otherwise strange bouncing effect
//	if(PhCollision.Var(a, tiles, TILE_SLOPE_LEFT))
//	{
		//Correct for left sloped tiles [/]
//		if(a.y != (TILE_SIZE - ((a.x) % TILE_SIZE) + ((a.y-1)/ TILE_SIZE)*TILE_SIZE))
//		{
//			return TILE_SIZE - ((a.x) % TILE_SIZE) + ((a.y-1)/ TILE_SIZE)*TILE_SIZE;
//		}
//	}
	// Using Var collision i.s.o. Sloped collision becaus otherwise strange bouncing effect
//	else if(PhCollision.Var(a, tiles, TILE_SLOPE_RIGHT))
//	{
		//Correct for left sloped tiles [\]
//		if(a.y != ((a.x) % TILE_SIZE) + ((a.y)/ TILE_SIZE)*TILE_SIZE)
//		{
//			return  ((a.x) % TILE_SIZE) + ((a.y)/ TILE_SIZE)*TILE_SIZE;
//		}
//	}
	if(a.y != (((a.y + a.h+(TILE_SIZE/4))/TILE_SIZE)*TILE_SIZE) - a.h)
	{
		return (((a.y + a.h+(TILE_SIZE/4))/TILE_SIZE) * TILE_SIZE) - a.h;
	}
	else
	{
		return a.y;
	}
}
