#include "Mobs.h"

Mobs::Mobs(int x, int y, int Type)
{
	MobBox.x = x;
	MobBox.y = y;
	MobBox.w = TILE_SIZE;
	MobBox.h = TILE_SIZE;
}

int Mobs::getType()
{
	return MobType;
}

SDL_Rect Mobs::getMobBox()
{
	return MobBox;
}

void Mobs::Render()
{
	
}