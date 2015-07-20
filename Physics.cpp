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
		cout << "fall test"  << endl;
		return true;
	}
	if(PhCollision.VarCollision(a, tiles, TILE_SLOPE_LEFT)) //[/]
	{
		cout << "fall test slope left" << endl;
		if(a.y + a.h >= (TILE_SIZE - ((a.x -1) + a.w) % TILE_SIZE) + ((a.y + a.h)/ TILE_SIZE)*TILE_SIZE)
		{
			return true;
		}
	}
	if(PhCollision.VarCollision(a, tiles, TILE_SLOPE_RIGHT)) //[\]
	{
		cout << "fall test slope right" << endl;
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
	if(PhCollision.VarCollision(a, tiles, TILE_SLOPE_LEFT))
	{
		cout << "stick test slope left" << endl;
		//Correct for left sloped tiles [/]
		return a.y;

	}
	else if(PhCollision.VarCollision(a, tiles, TILE_SLOPE_RIGHT))
	{
		cout << "stick test slope right" << endl;
		//Correct for left sloped tiles [\]
		if(a.y != ((a.x) % TILE_SIZE) + ((a.y-1)/ TILE_SIZE)*TILE_SIZE)
		{
			return  ((a.x) % TILE_SIZE) + ((a.y-1)/ TILE_SIZE)*TILE_SIZE;
		}
	}
	else if(a.y != (((a.y + a.h+(TILE_SIZE/4))/TILE_SIZE)*TILE_SIZE) - a.h)
	{
		cout << "stick test" << endl;
		return (((a.y + a.h+(TILE_SIZE/4))/TILE_SIZE) * TILE_SIZE) - a.h;
	}
	else
	{
	return a.y;
	}
}
