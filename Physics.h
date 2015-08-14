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
		bool Gravity_Rect(float timeStep, SDL_Rect a, Tile* tiles[]);
		bool Gravity_Box(float timeStep, Box a, Tile* tiles[]);
		int StickToFloor_Rect(SDL_Rect a, SDL_Rect b, Tile* tiles[]);
		int StickToFloor_Box(Box a, SDL_Rect b, Tile* tiles[]);
};

#endif // PHYSICS_H
