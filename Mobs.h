#ifndef MOBS_H
#define MOBS_H

#include <SDL.h>
#include <iostream>
#include "Textures.h"

using namespace std;

class Mobs
{
public:
    Mobs(int mobX, int mobY, int mobType, int weaponX, int weaponY, int weaponType);
    int getType();
    SDL_Rect getMobBox();
    SDL_Rect getWeaponBox();
    void Update();
    void Render(Textures* textures, SDL_Rect* clips, SDL_Renderer* Renderer, SDL_Rect* camera, double health);

    int MobType;
    int MobStatus;
    SDL_Rect MobBox;
    SDL_Rect HealthBar;
	SDL_Rect WeaponBox;
	//Created to compensate for camera movement
	SDL_Rect WeaponSprite;

protected:
private:
};

#endif // MOBS_H
