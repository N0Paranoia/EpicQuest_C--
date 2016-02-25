#ifndef AI_H
#define AI_H

#include <SDL.h>
#include "Constants.h"
#include "Mobs.h"
#include "Tile.h"

class Ai
{
public:
    Ai();
    virtual ~Ai();
    int Input(int i);
    void Agro(Mobs* mobs[], int i, SDL_Rect* playerRect, int type);
	int Attack(Mobs* mobs[], int i, SDL_Rect* playerRect, SDL_Rect* shieldRect, int axis);
    double Damage(Mobs* mobs[], int i, SDL_Rect* swordRect, int type);
    int Move(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect, SDL_Rect* swordRect, SDL_Rect* shieldRect, int type);
    int UpdateMovement(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect, SDL_Rect* swordRect, SDL_Rect* shieldRect, int type, int axis);
	int UpdateAttack(Mobs* mobs[], SDL_Rect* playerRect, SDL_Rect* shieldRect, int i, int axis);    
    int Physics(Mobs* mobs[], int i, Tile* tiles[]);
    int Health(int i, double damage);
    bool Alive(int i);
	void Debug();

    SDL_Rect WeaponBox[TOTAL_TILES];
protected:
private:
    SDL_Rect bottomCollisionBox;

    enum Movement
    {
        idle,
        left,
        right,
    };
    Movement movement[TOTAL_TILES] = {};

	bool isAttacking[TOTAL_TILES];
	int AttackCounter[TOTAL_TILES];
	int AttackDuration;
	int AttackDelay;

    double health[TOTAL_TILES];
    int Xvel[TOTAL_TILES];
    int Yvel[TOTAL_TILES];

    bool isFalling[TOTAL_TILES];
};

#endif // AI_H
