#include "Shadows.h"
#include "Constants.h"
#include "Textures.h"
#include "Collision.h"

Collision sCollision;

Shadows::Shadows(int x, int y, int Type)
{
	ShadowBox.x = x;
	ShadowBox.y = y;
	ShadowBox.w = TILE_SIZE;
	ShadowBox.h = 2*TILE_SIZE;

	ShadowType = Type;
}

int Shadows::getType()
{
	return ShadowType;
}

SDL_Rect Shadows::getShadowBox()
{
	return ShadowBox;
}

void Shadows::Render(Textures* textures, SDL_Rect* clips, SDL_Renderer* Renderer, SDL_Rect* camera)
{
	if(sCollision.Check(ShadowBox, *camera))
	{
		textures->Render(Renderer, ShadowBox.x - camera->x, ShadowBox.y - camera->y, &clips[ShadowType]);
	}
}
