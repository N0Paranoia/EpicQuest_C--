#ifndef PHYSICS_H
#define PHYSICS_H

#include <SDL.h>
#include "Tile.h"
#include "Constants.h"

class Physics
{
	private:
	public:
		Physics();
		virtual ~Physics();
		bool Gravity(SDL_Rect a, Tile* tiles[]);
		bool GravityBox(Box a, Tile* tiles[]);
		int StickToFloor(SDL_Rect a, SDL_Rect b, Tile* tiles[]);
		int StickToFloorBox(Box a, SDL_Rect b, Tile* tiles[]);
};

#endif // PHYSICS_H
