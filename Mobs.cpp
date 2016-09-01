#include "Mobs.h"
#include "Constants.h"
#include "Textures.h"
#include "Collision.h"

Collision mCollision;

Mobs::Mobs(int mobX, int mobY, int mobType, int weaponX, int weaponY, int weaponType) {
    MobBox.x = mobX;
    MobBox.y = mobY;
    MobBox.w = TILE_SIZE;
    MobBox.h = 2*TILE_SIZE;

    MobType = mobType;

    switch(mobType) {
    case MOB_TYPE_1:
        WeaponBox.x = weaponX;
        WeaponBox.y = weaponY;
        WeaponBox.w = TILE_SIZE;
        WeaponBox.h = 10;

	MovementSpeed = 2;
        break;
    default:
        WeaponBox.x = -TILE_SIZE;
        WeaponBox.y = -TILE_SIZE;
        WeaponBox.w = 0;
        WeaponBox.h = 0;
        break;
    }

}

int Mobs::getType() {
    return MobType;
}

SDL_Rect Mobs::getMobBox() {
    return MobBox;
}

SDL_Rect Mobs::getWeaponBox() {
    return WeaponBox;
}

void Mobs::Render(Textures* textures, SDL_Rect* clips, SDL_Renderer* Renderer, SDL_Rect* camera, double health) {
    SDL_SetRenderDrawColor(Renderer, 0xff, 0x00, 0x00, 0xff);
    HealthBar = {MobBox.x - camera->x, MobBox.y - camera->y - 10, ((health/100)*MobBox.w), 5};
    //Create weaponsprite to compensate for camera movement
    WeaponSprite = {WeaponBox.x - camera->x, WeaponBox.y - camera->y, WeaponBox.w, WeaponBox.h};
    if(mCollision.Check(MobBox, *camera)) {
        textures->Render(Renderer, MobBox.x - camera->x, MobBox.y - camera->y, &clips[MobType]);
        if(MobType > 0) {
            SDL_RenderFillRect(Renderer, &HealthBar);
            SDL_RenderFillRect(Renderer, &WeaponSprite);
        }
    }
}
