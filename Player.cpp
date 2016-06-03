#include "Player.h"
#include "Physics.h"
#include "Textures.h"
#include "Constants.h"
#include "Collision.h"
#include "Doors.h"

Textures SpriteSheetTexture;
Physics pPhysics;
Collision pCollision;
Doors pDoors;

Player::Player() {
  playerRect.x = 1*TILE_SIZE;
  playerRect.y = 2*TILE_SIZE;
  playerRect.w = TILE_SIZE;
  playerRect.h = 2*TILE_SIZE;

  Xvel = 0;
  Yvel = 0;
  walkingSpeed = 4;
  runningSpeed = 8;
  jumpHeight = 10;
  jumpingSpeed = jumpHeight + GRAVITY;
  frame = 0;
  StartFrameLeft = 7;
  EndFrameLeft = 0;
  StartFrameRight = 10;
  EndFrameRight = 17;
  IdleFrameLeft = 8;
  IdleFrameRight = 9;
  frameCounter = 0;
  frameSpeed = 12;
  frameSwitch = 60;

  jumpCount = 0;

  WalkingLeft = false;
  WalkingLeft = false;
  FacingLeft = false;
  FacingRight = true;
  isRunning = false;

  isFalling = true;

  isClimbing = false;
  canEnterDoor = true;

  canJump = true;
  isJumping = false;

  canRun = true;
  isRunning = false;

  isDucking = false;

  attack = false;
  isAttacking = false;
  block = false;
  isBlocking = false;

  maxHealth = 100;
  health = maxHealth;
  maxEnergy = 100;
  energy = maxEnergy;
  energyRecover = true;

  runEnergy = 2;
  jumpEnergy = 25;
  attackEnergy = 25;
  blockEnergy = 25;

  // int _state = state_idle;
}

Player::~Player() {
  //dtor
}

int Player::LoadMedia(SDL_Renderer* Renderer) {
  //Load Player spritesheet
  if(!(SpriteSheetTexture.LoadFromFile(Renderer, "assets/spriteSheet48.png"))) {
    cout << "Unable to load Player Texture! SDL_Error: " << SDL_GetError() << endl;
    return false;
  } else {
    PlayerClips[0].x = 0 * playerRect.w;
    PlayerClips[0].y = 0 * playerRect.h;
    PlayerClips[0].w = playerRect.w;
    PlayerClips[0].h = playerRect.h;

    PlayerClips[1].x = 1 * playerRect.w;
    PlayerClips[1].y = 0 * playerRect.h;
    PlayerClips[1].w = playerRect.w;
    PlayerClips[1].h = playerRect.h;

    PlayerClips[2].x = 2 * playerRect.w;
    PlayerClips[2].y = 0 * playerRect.h;
    PlayerClips[2].w = playerRect.w;
    PlayerClips[2].h = playerRect.h;

    PlayerClips[3].x = 3 * playerRect.w;
    PlayerClips[3].y = 0 * playerRect.h;
    PlayerClips[3].w = playerRect.w;
    PlayerClips[3].h = playerRect.h;

    PlayerClips[4].x = 4 * playerRect.w;
    PlayerClips[4].y = 0 * playerRect.h;
    PlayerClips[4].w = playerRect.w;
    PlayerClips[4].h = playerRect.h;

    PlayerClips[5].x = 5 * playerRect.w;
    PlayerClips[5].y = 0 * playerRect.h;
    PlayerClips[5].w = playerRect.w;
    PlayerClips[5].h = playerRect.h;

    PlayerClips[6].x = 6 * playerRect.w;
    PlayerClips[6].y = 0 * playerRect.h;
    PlayerClips[6].w = playerRect.w;
    PlayerClips[6].h = playerRect.h;

    PlayerClips[7].x = 7 * playerRect.w;
    PlayerClips[7].y = 0 * playerRect.h;
    PlayerClips[7].w = playerRect.w;
    PlayerClips[7].h = playerRect.h;

    PlayerClips[8].x = 8 * playerRect.w;
    PlayerClips[8].y = 0 * playerRect.h;
    PlayerClips[8].w = playerRect.w;
    PlayerClips[8].h = playerRect.h;

    PlayerClips[9].x = 9 * playerRect.w;
    PlayerClips[9].y = 0 * playerRect.h;
    PlayerClips[9].w = playerRect.w;
    PlayerClips[9].h = playerRect.h;

    PlayerClips[10].x = 10 * playerRect.w;
    PlayerClips[10].y = 0 * playerRect.h;
    PlayerClips[10].w = playerRect.w;
    PlayerClips[10].h = playerRect.h;

    PlayerClips[11].x = 11 * playerRect.w;
    PlayerClips[11].y = 0 * playerRect.h;
    PlayerClips[11].w = playerRect.w;
    PlayerClips[11].h = playerRect.h;

    PlayerClips[12].x = 12 * playerRect.w;
    PlayerClips[12].y = 0 * playerRect.h;
    PlayerClips[12].w = playerRect.w;
    PlayerClips[12].h = playerRect.h;

    PlayerClips[13].x = 13 * playerRect.w;
    PlayerClips[13].y = 0 * playerRect.h;
    PlayerClips[13].w = playerRect.w;
    PlayerClips[13].h = playerRect.h;

    PlayerClips[14].x = 14 * playerRect.w;
    PlayerClips[14].y = 0 * playerRect.h;
    PlayerClips[14].w = playerRect.w;
    PlayerClips[14].h = playerRect.h;

    PlayerClips[15].x = 15 * playerRect.w;
    PlayerClips[15].y = 0 * playerRect.h;
    PlayerClips[15].w = playerRect.w;
    PlayerClips[15].h = playerRect.h;

    PlayerClips[16].x = 16 * playerRect.w;
    PlayerClips[16].y = 0 * playerRect.h;
    PlayerClips[16].w = playerRect.w;
    PlayerClips[16].h = playerRect.h;

    PlayerClips[17].x = 17 * playerRect.w;
    PlayerClips[17].y = 0 * playerRect.h;
    PlayerClips[17].w = playerRect.w;
    PlayerClips[17].h = playerRect.h;
  }
  return true;
}

void Player::Input(Tile* tiles[], Mobs* mobs[]) {
  WalkingLeft = false;
  WalkingRight = false;

  keyState = SDL_GetKeyboardState(NULL);
  //State machine
  switch(_state) {
  case state_idle:
    Xvel = 0;
    if(keyState[SDL_SCANCODE_A]) {
      _state = state_walking;
    } else if(keyState[SDL_SCANCODE_D]) {
      _state = state_walking;
    }
    if(keyState[SDL_SCANCODE_S]) {
      isDucking = true;
      Yvel = walkingSpeed;
      this->Move(vertical, tiles);
      this->Climb(down, tiles);
    }
    if(!keyState[SDL_SCANCODE_S]) {
      isDucking = false;
    }
    if(keyState[SDL_SCANCODE_W]) {
      this->GoTroughDoor(tiles);
      this->Climb(up, tiles);
    }
    if(!keyState[SDL_SCANCODE_W]) {
      canEnterDoor = true;
    }
    if(keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT]) {
      _state = state_running;
    }
    if(keyState[SDL_SCANCODE_L]) {
      _state = state_attacking;
    }
    if(!keyState[SDL_SCANCODE_L]) {
      isAttacking = false;
    }
    if(keyState[SDL_SCANCODE_K]) {
      _state = state_blocking;
    }
    break;

  case state_walking:
    this->Move(horizontal, tiles);
    if(keyState[SDL_SCANCODE_A]) {
      Xvel = -walkingSpeed;
      WalkingLeft = true;
      FacingRight = false;
      FacingLeft = true;
    } else if(keyState[SDL_SCANCODE_D]) {

      Xvel = walkingSpeed;
      WalkingRight = true;
      FacingLeft = false;
      FacingRight = true;
    } else {
      _state = state_idle;
    }
    if(keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT]) {
      _state = state_running;
    }
    if(keyState[SDL_SCANCODE_L]) {
      _state = state_attacking;
    }
    if(keyState[SDL_SCANCODE_K]) {
      _state = state_blocking;
    }
    break;

  case state_running:
    if(keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT]) {
      if(Energy(0) > runEnergy && canRun) {
        if(keyState[SDL_SCANCODE_A]) {
          Xvel = -runningSpeed;
          this->Move(horizontal, tiles);
          this->Energy(runEnergy);
          WalkingLeft = true;
          FacingRight = false;
          FacingLeft = true;
        } else if(keyState[SDL_SCANCODE_D]) {
          Xvel = runningSpeed;
          this->Move(horizontal, tiles);
          this->Energy(runEnergy);
          WalkingRight = true;
          FacingLeft = false;
          FacingRight = true;
        }
        if(keyState[SDL_SCANCODE_SPACE]) {
          _state = state_jumping;
        }
        isRunning = true;
      } else {
        canRun = false;
        if(keyState[SDL_SCANCODE_A]) {
          Xvel = -walkingSpeed;
          this->Move(horizontal, tiles);
          this->Energy(runEnergy);
          WalkingLeft = true;
          FacingRight = false;
          FacingLeft = true;
        } else if(keyState[SDL_SCANCODE_D]) {
          Xvel = walkingSpeed;
          this->Move(horizontal, tiles);
          this->Energy(runEnergy);
          WalkingRight = true;
          FacingLeft = false;
          FacingRight = true;
        } else {
          isRunning = false;
          canRun = false;
        }
      }
    } else {
      isRunning = false;
      canRun = true;
      _state = state_idle;
    }
    break;

  case state_jumping:
    if(keyState[SDL_SCANCODE_SPACE]) {
      this->Jump(tiles);
    } else {
      _state = state_idle;
    }

    break;

  case state_climbing:
    if(keyState[SDL_SCANCODE_W]) {
      Yvel = -walkingSpeed;
      this->Move(vertical, tiles);
      this->Climb(up, tiles);
    } else if(keyState[SDL_SCANCODE_S]) {
      Yvel = walkingSpeed;
      this->Move(vertical, tiles);
      this->Climb(down, tiles);
    } else if(keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_D]) {
      isClimbing = false;
      _state = state_idle;
    }
    break;

  case state_attacking:
    if(keyState[SDL_SCANCODE_L]) {
      attack = true;
      this->Attack(mobs);
    } else {
      attack = false;
      this->Attack(mobs);
    }
    break;

  case state_blocking:
    if(keyState[SDL_SCANCODE_K]) {
      block = true;
      this->Block();
      if(keyState[SDL_SCANCODE_A]) {
        Xvel = -walkingSpeed/2;
        this->Move(horizontal, tiles);
      } else if(keyState[SDL_SCANCODE_D]) {
        Xvel = walkingSpeed/2;
        this->Move(horizontal, tiles);
      }
    } else {
      block = false;
      this->Block();
    }
    break;
  }
}

void Player::Falling(Tile* tiles[]) {
  if(!isClimbing && !isJumping) {
    playerRect.y += GRAVITY;
    if(pPhysics.Gravity(playerRect, tiles)) {
      playerRect.y -= GRAVITY;
      isFalling = false;
    } else {
      isFalling = true;
    }
    if(!isFalling) {
      // Hyper gravity to keep the player grounded
      if(!pCollision.Stick(bottomCollisionBox, tiles)) {
        playerRect.y = pPhysics.StickToFloor(playerRect, bottomCollisionBox, tiles);
      }
    }
  }
}
// -------------------------------------------------//
// ------------NEEDS WORK, IS OK FOR NOW------------//
// -------------------------------------------------//
void Player::Jump(Tile* tiles[]) {
  if(canJump) {
    if(jumpingSpeed > GRAVITY) {
      // if(FacingLeft)
      // {
      // 	Xvel = -runningSpeed;
      // }
      // else if(FacingRight)
      // {
      // 	Xvel = runningSpeed;
      // }
      Yvel = -jumpingSpeed;
      isClimbing = false;
      this->Energy(jumpEnergy);
      this->Move(jump, tiles);
      jumpingSpeed --;
      // jumpCount ++;
    } else {
      jumpCount = 0;
      jumpingSpeed = jumpHeight + GRAVITY;
      _state = state_walking;
    }
  }
}

void Player::Climb(int Movement, Tile* tiles[]) {
  if(pCollision.Var(vertCenterCollisionBox, tiles, TILE_LADDER) || pCollision.Var(vertCenterCollisionBox, tiles, TILE_LADDER_TOP)) {
    if(Movement == up || down) {
      _state = state_climbing;
      playerRect.y += Yvel;
      isClimbing = true;
      isFalling = false;
      // Stick to center of ladder
      playerRect.x = ((playerRect.x + (playerRect.w/2))/TILE_SIZE)*TILE_SIZE;
      if(Movement == down && pCollision.Wall(playerRect, tiles)) {
        playerRect.y -= Yvel;
      }
    }
  } else {
    isClimbing = false;
  }
}

void Player::GoTroughDoor(Tile* tiles[]) {
  if(pCollision.Var(vertCenterCollisionBox, tiles, TILE_DOOR)) {
    if(canEnterDoor) {
      pDoors.Connection(&playerRect, 0);
      canEnterDoor = false;
    }
  }
}

void Player::Attack(Mobs* mobs[]) {
  if(attack) {
    if(Energy(0) > attackEnergy) {
      if(FacingLeft) {
        if(pCollision.MobShield(SwordBox, mobs, MOB_TYPE_1)) {
          cout << "ShieldHit" << endl;
        } else {
          SwordBox = {this->playerRect.x - TILE_SIZE, this->playerRect.y + TILE_SIZE, TILE_SIZE, 10};
        }
      } else if(FacingRight) {
        if(pCollision.MobShield(SwordBox, mobs, MOB_TYPE_1)) {
          cout << "ShieldHit" << endl;
        } else {
          SwordBox = {this->playerRect.x + this->playerRect.w, this->playerRect.y + TILE_SIZE, TILE_SIZE, 10};
        }
      }
      if(!isAttacking) {
        Energy(attackEnergy);
        isAttacking = true;
        energyRecover = false;
      }
    } else {
      if(FacingLeft) {
        SwordBox = {this->playerRect.x - 10, this->playerRect.y + TILE_SIZE, 10, 10};
      } else if(FacingRight) {
        SwordBox = {this->playerRect.x + this->playerRect.w, this->playerRect.y + TILE_SIZE, 10, 10};
      }
    }
  } else {
    SwordBox = {0, 0, 0, 0};
    isAttacking = false;
    _state = state_idle;
    energyRecover = true;
  }
}

void Player::Block() {
  if(block) {
    if(Energy(0) > blockEnergy) {
      if(FacingLeft) {
        ShieldBox = {this->playerRect.x - 10, this->playerRect.y, 10, playerRect.h};
      } else if(FacingRight) {
        ShieldBox = {this->playerRect.x + this->playerRect.w, this->playerRect.y, 10, playerRect.h};
      }
      if(!isBlocking) {
        Energy(blockEnergy);
        isBlocking = true;
        energyRecover = false;
      }
    } else {
      if(FacingLeft) {
        ShieldBox = {this->playerRect.x - 2, this->playerRect.y, 2, playerRect.h};
      }
      if(FacingRight) {
        ShieldBox = {this->playerRect.x + this->playerRect.w, this->playerRect.y, 2, playerRect.h};
      }
    }
  } else {
    ShieldBox = {0, 0, 0, 0};
    isBlocking = false;
    _state = state_idle;
    energyRecover = true;
  }
}

void Player::Move(int Movement, Tile* tiles[]) {
  if(!isAttacking) {
    // Horizontal movement
    if(Movement == horizontal || Movement == jump) {
      playerRect.x += Xvel;
    }
    // Horizontal collision handling
    if(playerRect.x < 0 || playerRect.x + playerRect.w > LEVEL_WIDTH*TILE_SIZE || pCollision.Wall(playerRect, tiles)) {
      playerRect.x -= Xvel;
    }
    // Horizontal Slope collision handling
    if(pCollision.Slope_45_Left(playerRect, tiles)) { //[/]
      if((TILE_SIZE - ((playerRect.x) + (playerRect.w-1)) % TILE_SIZE) == 1) {
        // compesate for colliding in to next tile becoude of the playerRect.w -1
        playerRect.y = ((TILE_SIZE - ((playerRect.x) + (playerRect.w-1)) % TILE_SIZE) + ((playerRect.y-1)/ TILE_SIZE)*TILE_SIZE) -1;
      } else if(isRunning && TILE_SIZE - ((playerRect.x + playerRect.w-1)) % TILE_SIZE <= runningSpeed) {
        // composate for collidoing in to next tiles becouse of running
        playerRect.y = ((TILE_SIZE - ((playerRect.x) + (playerRect.w-1)) % TILE_SIZE) + ((playerRect.y-1)/ TILE_SIZE)*TILE_SIZE) -runningSpeed;
      } else if(TILE_SIZE - (playerRect.x + playerRect.w-1) % TILE_SIZE <= walkingSpeed) {
        // composate for collidoing in to next tiles of decelerating
        playerRect.y = ((TILE_SIZE - ((playerRect.x) + (playerRect.w-1)) % TILE_SIZE) + ((playerRect.y-1)/ TILE_SIZE)*TILE_SIZE) -walkingSpeed;
      } else {
        playerRect.y = (TILE_SIZE - ((playerRect.x) + (playerRect.w-1)) % TILE_SIZE) + ((playerRect.y-1)/ TILE_SIZE)*TILE_SIZE;
      }
    }
    if(pCollision.Slope_45_Right(playerRect, tiles)) { //[\]
      if(isRunning && ((playerRect.x) % TILE_SIZE) <= runningSpeed) {
        // composate for collidoing in to next tiles becouse of running
        playerRect.y = ((playerRect.x) % TILE_SIZE) + ((playerRect.y-1)/ TILE_SIZE)*TILE_SIZE -runningSpeed;
      } else if((playerRect.x % TILE_SIZE) <= walkingSpeed) {
        // composate for collidoing in to next tiles of decelerating
        playerRect.y = ((playerRect.x) % TILE_SIZE) + ((playerRect.y-1)/ TILE_SIZE)*TILE_SIZE -walkingSpeed;
      } else {
        playerRect.y = ((playerRect.x) % TILE_SIZE) + ((playerRect.y-1)/ TILE_SIZE)*TILE_SIZE;
      }
    }
    // Vertical movement
    if(Movement == vertical  || Movement == jump)
      playerRect.y += Yvel;
    // Vertical collision handling
    if(playerRect.y < 0 || playerRect.y + playerRect.h > LEVEL_HEIGHT*TILE_SIZE ||
        pCollision.Wall(playerRect, tiles) ||
        pCollision.Slope_45_Right(playerRect, tiles) ||
        pCollision.Slope_45_Left(playerRect, tiles)
      )
      playerRect.y -= Yvel;
  }
}

int Player::Health(int damage) {
  health = health - damage;
  if(health <=0) {
    health = 0;
  }
  return health;
}

int Player::Energy(int action) {
  if(energy <= 0) {
    energy = 0;
  }
  if(_state == state_idle || _state == state_walking) {
    if(energyRecover && action == 0 && energy < maxEnergy) {
      energy ++;
    }
  }
  energy = energy - action;
  return energy;
}

void Player::MobsCollision(Mobs* mobs[], int i) {

  if(pCollision.Mob(playerRect, mobs, MOB_TYPE_1)) {
    this->Health(5);
  }
  if(pCollision.MobWeapon(playerRect, mobs, MOB_TYPE_1) && !isBlocking) {
    this->Health(5);
  }
}

void Player::Render(SDL_Renderer* Renderer, SDL_Rect* camera) {
  frameCounter += frameSpeed;
  if(frameCounter > frameSwitch) {
    // Walking Animation
    if(WalkingLeft) {

      frame --;
      frameCounter = 0;
      if(frame < EndFrameLeft || frame > StartFrameLeft) {
        frame = StartFrameLeft;
      }
    } else {
      //Idle frame left
      if(FacingLeft) {
        frame = IdleFrameLeft;
      }
    }
    if(WalkingRight) {
      frame ++;
      frameCounter = 0;
      if(frame  > EndFrameRight || frame < StartFrameRight) {
        frame = StartFrameRight;
      }
    } else {
      //Idle frame right
      if(FacingRight) {
        frame = IdleFrameRight;
      }
    }
  }
  //Show collsiion box
  SDL_SetRenderDrawColor(Renderer, 0xff, 0x00, 0x00, 0xff);
  playerBox = {playerRect.x - camera->x, playerRect.y - camera->y, playerRect.w, playerRect.h};
  SDL_RenderFillRect(Renderer, &playerBox);

  //Create New Rectangle for sword for the camera compisation
  Sword = {SwordBox.x - camera->x, SwordBox.y - camera->y, SwordBox.w, SwordBox.h};
  SDL_RenderFillRect(Renderer, &Sword);

  HealthBar = {10, 10, this->Health(0), 10};
  StaminBar = {10, 25, this->Energy(0), 10};
  SDL_RenderFillRect(Renderer, &HealthBar);
  SDL_SetRenderDrawColor(Renderer, 0x00, 0xff, 0x00, 0xFF);
  SDL_RenderFillRect(Renderer, &StaminBar);
  //Render Frame
  SpriteSheetTexture.Render(Renderer, playerRect.x - camera->x, playerRect.y - camera->y, &PlayerClips[frame]);
  SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0xff, 0xff);
  //Create New Rectangle for shield for the camera compisation
  Shield = {ShieldBox.x - camera->x, ShieldBox.y - camera->y, ShieldBox.w, ShieldBox.h};
  SDL_RenderFillRect(Renderer, &Shield);
}

void Player::Update(Mobs* mobs[]) {
  // initiolize bottomCollisionBox
  bottomCollisionBox = {playerRect.x, (playerRect.y + playerRect.h), playerRect.w, 1};
  // initialize vertCenterCollisionBox
  vertCenterCollisionBox = {playerRect.x + (playerRect.w/2), playerRect.y, 2, playerRect.h+1};
  // Update the Mobcollision
  //this->MobsCollision(mobs);
  for(int i = 0; i < TOTAL_TILES; i++) {
    this->MobsCollision(mobs, i);
  }
}

void Player::Cleanup() {
  SpriteSheetTexture.Free();
}
