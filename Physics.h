#ifndef PHYSICS_H
#define PHYSICS_H

#include <SDL.h>
#include "Tile.h"

class Physics
{
	private:
	public:
		Physics();
		virtual ~Physics();
		bool Gravity(SDL_Rect a, Tile* tiles[]);
		int StickToFloor(SDL_Rect a, Tile* tiles[]);
};

#endif // PHYSICS_H
