#include "Mobs.h"
#include "Constants.h"
#include "Textures.h"
#include "Collision.h"

Collision mCollision;

Mobs::Mobs(int x, int y, int Type)
{
	MobBox.x = x;
	MobBox.y = y;
	MobBox.w = TILE_SIZE;
	MobBox.h = 2*TILE_SIZE;

	MobType = Type;
}

int Mobs::getType()
{
	return MobType;
}

SDL_Rect Mobs::getMobBox()
{
	return MobBox;
}

void Mobs::Render(Textures* textures, SDL_Rect* clips, SDL_Renderer* Renderer, SDL_Rect* camera)
{
	if(mCollision.Check(MobBox, *camera))
	{
    	textures->Render(Renderer, MobBox.x - camera->x, MobBox.y - camera->y, &clips[MobType]);
	}
}
