#ifndef AI_H
#define AI_H

#include <SDL.h>
#include "Constants.h"
#include "Mobs.h"
#include "Tile.h"

class Ai {
public:
  Ai();
  virtual ~Ai();
  int Input(int i);
  void Patrolling(int i, int type);
  void Agro(Mobs* mobs[], int i, SDL_Rect* playerRect, int type);
  int Attack(Mobs* mobs[], int i, SDL_Rect* playerRect, SDL_Rect* shieldRect, int axis);
  int Block(Mobs* mobs[], int i, int axis);
  double Damage(Mobs* mobs[], int i, SDL_Rect* swordRect, int type);
  int Move(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* swordRect, SDL_Rect* shieldRect);
  int UpdateMovement(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect, SDL_Rect* swordRect, SDL_Rect* shieldRect, int type, int axis);
  int UpdateAttack(Mobs* mobs[], SDL_Rect* playerRect, SDL_Rect* shieldRect, int i, int axis);
  int UpdateBlock(Mobs* mobs[], int i, int axis);
  int Physics(Mobs* mobs[], int i, Tile* tiles[]);
  int Health(int i, double damage);
  bool Alive(int i);
  void Debug();

  SDL_Rect WeaponBox[TOTAL_TILES];
protected:
private:
  SDL_Rect bottomCollisionBox;

  enum Movement {
    idle,
    left,
    right,
    patrolling
  };
  Movement movement[TOTAL_TILES] = {};

  bool inAgroRange[TOTAL_TILES];
  
  bool facingLeft[TOTAL_TILES];
  bool facingRight[TOTAL_TILES];

  bool isAttacking[TOTAL_TILES];
  bool isBlocking[TOTAL_TILES];
  int AttackCounter[TOTAL_TILES];
  int AttackDelayCounter[TOTAL_TILES];
  int AttackDuration;
  int AttackAnimationDelay;

  double health[TOTAL_TILES];
  int Xvel[TOTAL_TILES];
  int Yvel[TOTAL_TILES];

  bool isFalling[TOTAL_TILES];

  int rnd_direction[TOTAL_TILES];
  int test_number;
};

#endif // AI_H
