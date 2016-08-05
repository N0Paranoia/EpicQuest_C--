#include "Ai.h"
#include "Constants.h"
#include "Collision.h"
#include "Physics.h"
#include <random>

Collision aiCollision;
Physics aiPhysics;

Ai::Ai() {
  for(int i = 0; i < TOTAL_TILES; i++) {
    isFalling[i] = true;
    health[i] = 100;
    isAttacking[i] = false;
    isBlocking[i] = true;
    facingLeft[i] = true;
    facingRight[i] = false;
    inAgroRange[i] = false;
  }
  AttackCounter[TOTAL_TILES] = 0;
  AttackDelayCounter[TOTAL_TILES] = 0;
  AttackDuration = 30;
  AttackAnimationDelay = 120;
  movementSpeed = 2;
}

Ai::~Ai() {
  //dtor
}

int Ai::Input(int i) {
  if(movement[i] == left) {
    facingRight[i] = false;
    facingLeft[i] = true;
    return -movementSpeed;
  }
  if(movement[i] == right) {
    facingLeft[i] = false;
    facingRight[i] = true;
    return movementSpeed;
  }
  if(movement[i] == idle) {
    return 0;
  }
  return 0;
}

void Ai::Patrolling(int i, int type) {
  if(!inAgroRange[i]) {
    if(test_number > FPS) {
      rnd_direction[i] = (rand() % 3);
      test_number = 0;
    } else {
      test_number ++;
    }
    if(rnd_direction[i] == 0) {
      movement[i] = idle;    
    }
    else if(rnd_direction[i] == 1) {
      movement[i] = left;
    }
    else if(rnd_direction[i] == 2 ) {
      movement[i] = right;
    } else {
      movement[i] = idle;
    }
  }
}

void Ai::Agro(Mobs* mobs[], int i, SDL_Rect* playerRect, int type) {
  switch(type) {
  case MOB_TYPE_1:
    // Check vertical alighnement
    if(playerRect->y > (mobs[i]->getMobBox().y - AGRO_RANGE) && playerRect->y < ((mobs[i]->getMobBox().y + mobs[i]->getMobBox().h) + AGRO_RANGE)) {
      // Check Horizontal alighnment
      if(playerRect->x + playerRect->w + (playerRect->w/2) < mobs[i]->getMobBox().x && playerRect->x + playerRect->w > mobs[i]->getMobBox().x - AGRO_RANGE) {
	inAgroRange[i] = true;
	movement[i] = left;
      }
      // Check Horizontal alighnment
      else if(playerRect->x - (playerRect->w/2) > (mobs[i]->getMobBox().x + mobs[i]->getMobBox().w) && playerRect->x < (mobs[i]->getMobBox().x + mobs[i]->getMobBox().w) + AGRO_RANGE) {
	inAgroRange[i] = true;
        movement[i] = right;
      }
      inAgroRange[i] = false;
    }
    inAgroRange[i] = false;
    break;
  }
}

int Ai::Attack(Mobs* mobs[], int i, SDL_Rect* playerRect, SDL_Rect* shieldRect, int axis) {
  isAttacking[i] = true;
  switch(axis) {
  case X_AXIS:
    // If the player is LEFT of the mob
    if(facingLeft[i]) {
      // If mob weapon bounces of the player shield
      if(aiCollision.Check(mobs[i]->getWeaponBox(), *shieldRect)) {
	return mobs[i]->getMobBox().x;
      } else {
	return mobs[i]->getMobBox().x - TILE_SIZE;
      }
    }
    // If the Player is RIGHT of the mob
    else if(facingRight[i]) {
      // If mob weapon bounces of the player shield
      if(aiCollision.Check(mobs[i]->getWeaponBox(), *shieldRect)) {
	return mobs[i]->getMobBox().x;
      } else {
	return mobs[i]->getMobBox().x + TILE_SIZE;
      }
    } else {
      return -TILE_SIZE;
    }
    break;

  case Y_AXIS:
    // If the player is OBOVE the mob
    if(playerRect->y <= mobs[i]->getMobBox().y) {
      // If mob weapon bounces of the player shield
      if(aiCollision.Check(mobs[i]->getWeaponBox(), *shieldRect)) {
	return mobs[i]->getMobBox().y;
      } else {
	return mobs[i]->getMobBox().y + ((mobs[i]->getMobBox().h/2)-10);
      }
    }
    // If the plalyer is BELOW the mob
    else if(playerRect->y >= mobs[i]->getMobBox().y) {
      // If mob weapon bounces of the player shield
      if(aiCollision.Check(mobs[i]->getWeaponBox(), *shieldRect)) {
	return mobs[i]->getMobBox().y;
      } else {
	return mobs[i]->getMobBox().y + (mobs[i]->getMobBox().h/2);
      }
    } else {
      return -TILE_SIZE;
    }
    break;
  }
  return 0;
}

int Ai::Block(Mobs* mobs[], int i, int axis) {
  switch(axis) {
  case X_AXIS:
    if(facingLeft[i]) {
      return mobs[i]->getMobBox().x - mobs[i]->getShieldBox().w;
    } else if(facingRight[i]) {
      return mobs[i]->getMobBox().x + mobs[i]->getMobBox().w;
    }
    break;
  case Y_AXIS:
    return mobs[i]->getMobBox().y + (mobs[i]->getMobBox().h/4);
    break;
  }
  return 0;
}

double Ai::Damage(Mobs* mobs[], int i, SDL_Rect* swordRect, int type) {
  switch(type) {
  case MOB_TYPE_1:
    if(aiCollision.Rect(mobs[i]->getMobBox(), *swordRect)) {
      cout << "Auw" << endl;
      return 10;
    }
    break;
  }
  return 0;
}

int Ai::Physics(Mobs* mobs[], int i, Tile* tiles[]) {
  bottomCollisionBox = { mobs[i]->getMobBox().x, (mobs[i]->getMobBox().y +  mobs[i]->getMobBox().h),  mobs[i]->getMobBox().w, 1};

  if(!aiCollision.Stick(bottomCollisionBox, tiles)) {
    return aiPhysics.StickToFloor( mobs[i]->getMobBox(), bottomCollisionBox, tiles);
  } else if(aiCollision.Slope_45_Left(mobs[i]->getMobBox(), tiles)) { //[/]
    // compesate for colliding in to next tile becoude of the playerRect.w -1
    return ((TILE_SIZE - ((mobs[i]->getMobBox().x) + (mobs[i]->getMobBox().w-1)) % TILE_SIZE) + ((mobs[i]->getMobBox().y-1)/ TILE_SIZE)*TILE_SIZE) -1;
  } else if(aiCollision.Slope_45_Right(mobs[i]->getMobBox(), tiles)) { //[/])
    return ((mobs[i]->getMobBox().x) % TILE_SIZE) + ((mobs[i]->getMobBox().y-1)/ TILE_SIZE)*TILE_SIZE;
  }
  return mobs[i]->getMobBox().y;
}

int Ai::Health(int i, double damage) {
  if(!isBlocking[i]) {
    health[i] = (health[i] - damage);
  }
  return health[i];
}

bool Ai::Alive(int i) {
  if(this->Health(i, 0) > 0) {
    return true;
  } else {
    return false;
  }
}

int Ai::Move(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* swordRect, SDL_Rect* shieldRect) {
  //----Basic Wallcollision Ai----(and bounce of shield)----(and sword knockback)----//
  if(aiCollision.Wall(mobs[i]->getMobBox(), tiles) || aiCollision.Rect(mobs[i]->getMobBox(), *swordRect) || aiCollision.Rect(mobs[i]->getMobBox(), *shieldRect)) {
    if(movement[i] == left) {
      movement[i] = right;
    } else if(movement[i] == right) {
      movement[i] = left;
    }
  }
  //----Basic Wallcollision Ai----//
  return mobs[i]->getMobBox().x + this->Input(i);
}


int Ai::UpdateBlock(Mobs* mobs[], int i, int axis) {
  if(!isAttacking[i]) {
    isBlocking[i] = true;
    switch(axis) {
    case X_AXIS:
      return this->Block(mobs, i, axis);
      break;
    case Y_AXIS:
      return this->Block(mobs, i, axis);
      break;
    }
  } else {
    isBlocking[i] = false;
    return -TILE_SIZE;
  }
  return 0;
}

int Ai::UpdateAttack(Mobs* mobs[], SDL_Rect* playerRect, SDL_Rect* shieldRect, int i, int axis) {
  // Check vertica and Horizontal alighnment
  if((playerRect->y + playerRect->h) >= (mobs[i]->getMobBox().y - ATTACK_RANGE_MELEE) && playerRect->y <= ((mobs[i]->getMobBox().y + mobs[i]->getMobBox().h) + ATTACK_RANGE_MELEE)&&(playerRect->x + playerRect->w) >= (mobs[i]->getMobBox().x- ATTACK_RANGE_MELEE) && playerRect->x <= ((mobs[i]->getMobBox().x + mobs[i]->getMobBox().w) + ATTACK_RANGE_MELEE)) {
    // Creating attack delay
    if(AttackCounter[i] > AttackAnimationDelay) {
      if(AttackDelayCounter[i] > AttackDuration) {
	isAttacking[i] = false;
	AttackCounter[i] = 0;
      }
      AttackDelayCounter[i] ++;
      
      switch(axis) {
      case X_AXIS:
	return this->Attack(mobs, i, playerRect, shieldRect, X_AXIS);
	break;

      case Y_AXIS:
	return this->Attack(mobs, i, playerRect, shieldRect, Y_AXIS);
	break;
      }
    } else {
      isAttacking[i] = false;
      AttackDelayCounter[i] = 0;
      AttackCounter[i] ++;
      return - TILE_SIZE;
    }
  }
  return 0;
}

int Ai::UpdateMovement(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect, SDL_Rect* swordRect, SDL_Rect* shieldRect, int type, int axis) {
  //---- Basic Ai "input"----//
  this->Input(i);
  //---- Badic Ai Patreolling ----//
  this->Patrolling(i, type);
  //----Basic Agro Ai----//
  this->Agro(mobs, i, playerRect, type);
  //----Basic Damage taking Ai----//
  this->Damage(mobs, i, swordRect, type);
  //----Basic AI attack ----//

  switch(axis) {
  case X_AXIS:
    //----Basic Ai Horizontal Movement and collision ----//
    return this->Move(mobs, i, tiles, swordRect, shieldRect);
    break;

  case Y_AXIS:
    return this->Physics(mobs, i, tiles);
    break;
  }
  return 0;
}

void Ai::Debug() {
  // Set breakline 260 for debugging
  cout << "Debug!" << endl;
  // Test random number
  cout << (rand() % 10) << endl;
}
