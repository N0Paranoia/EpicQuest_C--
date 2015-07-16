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
	if(PhCollision.WallCollision(a, tiles) || PhCollision.CloudCollision(a, tiles))
	{
		return true;
	}
	if(PhCollision.VarCollision(a, tiles, TILE_SLOPE_LEFT))
	{
		if(a.y + a.h >= (TILE_SIZE - ((a.x -1) + a.w) % TILE_SIZE) + ((a.y + a.h)/ TILE_SIZE)*TILE_SIZE)
		{
			return true;
		}
	}
	if(PhCollision.VarCollision(a, tiles, TILE_SLOPE_RIGHT))
	{
		if(a.y + a.h >= ((a.x) % TILE_SIZE) + ((a.y + a.h) / TILE_SIZE)*TILE_SIZE)
		{
			return true;
		}
	}
	return false;
}

int Physics::StickToFloor(SDL_Rect a, Tile* tiles[])
{
	// Correct if object is floating due fast collision
	if(!PhCollision.VarCollision(a, tiles, TILE_SLOPE_LEFT) || !PhCollision.VarCollision(a, tiles, TILE_SLOPE_RIGHT))
	{
		if(a.y != (((a.y + a.h+(TILE_SIZE/4))/TILE_SIZE)*TILE_SIZE) - a.h)
		{
			return (((a.y + a.h+(TILE_SIZE/4))/TILE_SIZE) * TILE_SIZE) - a.h;
		}
		else
		{
		return a.y;
		}
	}
	else
	{
		return a.y;
	}
}
