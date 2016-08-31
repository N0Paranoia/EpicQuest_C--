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

int Physics::StickToFloor(SDL_Rect a, SDL_Rect b, Tile* tiles[])
{
	// Correct if object is floating due (fast) collision
	if(PhCollision.Var(b, tiles, TILE_SLOPE_LEFT))
	{
		if((TILE_SIZE - ((a.x) + (a.w-1)) % TILE_SIZE) == 1)
		{
			// compesate for colliding in to next tile becoude of the a.w -1
			return ((a.y)/ TILE_SIZE)*TILE_SIZE;
		}
		return (TILE_SIZE - ((a.x) + (a.w-1)) % TILE_SIZE) + ((a.y)/ TILE_SIZE)*TILE_SIZE;
	}
	else if(PhCollision.Var(b, tiles, TILE_SLOPE_RIGHT))
	{
		return ((a.x) % TILE_SIZE) + ((a.y)/ TILE_SIZE)*TILE_SIZE;
	}
	else
	{
		return (((a.y + a.h+(TILE_SIZE/4))/TILE_SIZE) * TILE_SIZE) - a.h;
	}
}
