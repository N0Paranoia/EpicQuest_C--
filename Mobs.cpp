#include "Mobs.h"
#include "Constants.h"
#include "Textures.h"
#include "Collision.h"

Collision mCollision;

Mobs::Mobs(int mobX, int mobY, int mobType, int weaponX, int weaponY, int weaponType, int shieldX, int shieldY)
{
	MobBox.x = mobX;
	MobBox.y = mobY;
	MobBox.w = TILE_SIZE;
	MobBox.h = 2*TILE_SIZE;

	MobType = mobType;

	switch(mobType)
	{
		case MOB_TYPE_1:
			WeaponBox.x = weaponX;
			WeaponBox.y = weaponY;
			WeaponBox.w = TILE_SIZE;
			WeaponBox.h = 10;

            ShieldBox.x = shieldX;
            ShieldBox.y = shieldY;
            ShieldBox.w = 10;
            ShieldBox.h = TILE_SIZE;

			break;
		default:
			WeaponBox.x = -TILE_SIZE;
			WeaponBox.y = -TILE_SIZE;
			WeaponBox.w = 0;
			WeaponBox.h = 0;

            ShieldBox.x = shieldX;
            ShieldBox.y = shieldY;
            ShieldBox.w = 10;
            ShieldBox.h = TILE_SIZE;

			break;
	}

}

int Mobs::getType()
{
	return MobType;
}

SDL_Rect Mobs::getMobBox()
{
	return MobBox;
}

SDL_Rect Mobs::getWeaponBox()
{
	return WeaponBox;
}

SDL_Rect Mobs::getShieldBox()
{
    return ShieldBox;
}

void Mobs::Render(Textures* textures, SDL_Rect* clips, SDL_Renderer* Renderer, SDL_Rect* camera, double health)
{
	SDL_SetRenderDrawColor(Renderer, 0xff, 0x00, 0x00, 0xff);
	HealthBar = {MobBox.x - camera->x, MobBox.y - camera->y - 10, ((health/100)*MobBox.w), 5};
	//Create weaponsprite to compensate for camera movement
	WeaponSprite = {WeaponBox.x - camera->x, WeaponBox.y - camera->y, WeaponBox.w, WeaponBox.h};
    ShieldSprite = {ShieldBox.x - camera->x, ShieldBox.y - camera->y, ShieldBox.w, ShieldBox.h};
	if(mCollision.Check(MobBox, *camera))
	{
		textures->Render(Renderer, MobBox.x - camera->x, MobBox.y - camera->y, &clips[MobType]);
		if(MobType > 0)
		{
			SDL_RenderFillRect(Renderer, &HealthBar);
			SDL_RenderFillRect(Renderer, &WeaponSprite);
            SDL_RenderFillRect(Renderer, &ShieldSprite);
		}
	}
}
