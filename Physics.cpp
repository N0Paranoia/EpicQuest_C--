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
	if(PhCollision.Wall(a, tiles) || PhCollision.Cloud(a, tiles))
	{
		return true;
	}
	if(PhCollision.Var(a, tiles, TILE_SLOPE_LEFT)) //[/]
	{
		if(a.y >= (TILE_SIZE - ((a.x -1) + a.w) % TILE_SIZE) + ((a.y)/ TILE_SIZE)*TILE_SIZE)
		{
			return true;
		}
	}
	if(PhCollision.Var(a, tiles, TILE_SLOPE_RIGHT)) //[\]
	{
		if(a.y >= ((a.x) % TILE_SIZE) + ((a.y) / TILE_SIZE)*TILE_SIZE)
		{
			return true;
		}
	}
	return false;
}

int Physics::StickToFloor(SDL_Rect a, Tile* tiles[])
{
	// Correct if object is floating due fast collision
	if(PhCollision.Var(a, tiles, TILE_SLOPE_LEFT))
	{
		//Correct for left sloped tiles [/]
		return a.y;

	}
	else if(PhCollision.Var(a, tiles, TILE_SLOPE_RIGHT))
	{
		//Correct for left sloped tiles [\]
		if(a.y != ((a.x) % TILE_SIZE) + ((a.y-1)/ TILE_SIZE)*TILE_SIZE)
		{
			return  ((a.x) % TILE_SIZE) + ((a.y-1)/ TILE_SIZE)*TILE_SIZE;
		}
	}
	else if(a.y != (((a.y + a.h+(TILE_SIZE/4))/TILE_SIZE)*TILE_SIZE) - a.h)
	{
		return (((a.y + a.h+(TILE_SIZE/4))/TILE_SIZE) * TILE_SIZE) - a.h;
	}
	else
	{
	return a.y;
	}
}
