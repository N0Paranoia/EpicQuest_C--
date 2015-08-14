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

Player::Player()
{
	walkingSpeed = 200;
	runningSpeed = 400;
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
	frameSpeed = 25;
	//delay for smooth animation
	frameSwitch = 2;

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
	
	int _state = state_idle;

	_PlayerBox.x = 2*TILE_SIZE;
	_PlayerBox.y = 2*TILE_SIZE;
	_PlayerBox.w = TILE_SIZE;
	_PlayerBox.h = 2*TILE_SIZE;
}

Player::~Player()
{
	//dtor
}

int Player::LoadMedia(SDL_Renderer* Renderer)
{
	//Load Player spritesheet
	if((SpriteSheetTexture.LoadFromFile(Renderer, "assets/spriteSheet48.png")) == NULL)
	{
		cout << "Unable to load Player Texture! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		PlayerClips[0].x = 0 * _PlayerBox.w;
		PlayerClips[0].y = 0 * _PlayerBox.h;
		PlayerClips[0].w = _PlayerBox.w;
		PlayerClips[0].h = _PlayerBox.h;

		PlayerClips[1].x = 1 * _PlayerBox.w;
		PlayerClips[1].y = 0 * _PlayerBox.h;
		PlayerClips[1].w = _PlayerBox.w;
		PlayerClips[1].h = _PlayerBox.h;

		PlayerClips[2].x = 2 * _PlayerBox.w;
		PlayerClips[2].y = 0 * _PlayerBox.h;
		PlayerClips[2].w = _PlayerBox.w;
		PlayerClips[2].h = _PlayerBox.h;

		PlayerClips[3].x = 3 * _PlayerBox.w;
		PlayerClips[3].y = 0 * _PlayerBox.h;
		PlayerClips[3].w = _PlayerBox.w;
		PlayerClips[3].h = _PlayerBox.h;

		PlayerClips[4].x = 4 * _PlayerBox.w;
		PlayerClips[4].y = 0 * _PlayerBox.h;
		PlayerClips[4].w = _PlayerBox.w;
		PlayerClips[4].h = _PlayerBox.h;

		PlayerClips[5].x = 5 * _PlayerBox.w;
		PlayerClips[5].y = 0 * _PlayerBox.h;
		PlayerClips[5].w = _PlayerBox.w;
		PlayerClips[5].h = _PlayerBox.h;

		PlayerClips[6].x = 6 * _PlayerBox.w;
		PlayerClips[6].y = 0 * _PlayerBox.h;
		PlayerClips[6].w = _PlayerBox.w;
		PlayerClips[6].h = _PlayerBox.h;

		PlayerClips[7].x = 7 * _PlayerBox.w;
		PlayerClips[7].y = 0 * _PlayerBox.h;
		PlayerClips[7].w = _PlayerBox.w;
		PlayerClips[7].h = _PlayerBox.h;

		PlayerClips[8].x = 8 * _PlayerBox.w;
		PlayerClips[8].y = 0 * _PlayerBox.h;
		PlayerClips[8].w = _PlayerBox.w;
		PlayerClips[8].h = _PlayerBox.h;

		PlayerClips[9].x = 9 * _PlayerBox.w;
		PlayerClips[9].y = 0 * _PlayerBox.h;
		PlayerClips[9].w = _PlayerBox.w;
		PlayerClips[9].h = _PlayerBox.h;

		PlayerClips[10].x = 10 * _PlayerBox.w;
		PlayerClips[10].y = 0 * _PlayerBox.h;
		PlayerClips[10].w = _PlayerBox.w;
		PlayerClips[10].h = _PlayerBox.h;

		PlayerClips[11].x = 11 * _PlayerBox.w;
		PlayerClips[11].y = 0 * _PlayerBox.h;
		PlayerClips[11].w = _PlayerBox.w;
		PlayerClips[11].h = _PlayerBox.h;

		PlayerClips[12].x = 12 * _PlayerBox.w;
		PlayerClips[12].y = 0 * _PlayerBox.h;
		PlayerClips[12].w = _PlayerBox.w;
		PlayerClips[12].h = _PlayerBox.h;

		PlayerClips[13].x = 13 * _PlayerBox.w;
		PlayerClips[13].y = 0 * _PlayerBox.h;
		PlayerClips[13].w = _PlayerBox.w;
		PlayerClips[13].h = _PlayerBox.h;

		PlayerClips[14].x = 14 * _PlayerBox.w;
		PlayerClips[14].y = 0 * _PlayerBox.h;
		PlayerClips[14].w = _PlayerBox.w;
		PlayerClips[14].h = _PlayerBox.h;

		PlayerClips[15].x = 15 * _PlayerBox.w;
		PlayerClips[15].y = 0 * _PlayerBox.h;
		PlayerClips[15].w = _PlayerBox.w;
		PlayerClips[15].h = _PlayerBox.h;

		PlayerClips[16].x = 16 * _PlayerBox.w;
		PlayerClips[16].y = 0 * _PlayerBox.h;
		PlayerClips[16].w = _PlayerBox.w;
		PlayerClips[16].h = _PlayerBox.h;

		PlayerClips[17].x = 17 * _PlayerBox.w;
		PlayerClips[17].y = 0 * _PlayerBox.h;
		PlayerClips[17].w = _PlayerBox.w;
		PlayerClips[17].h = _PlayerBox.h;
	}
	return true;
}


void Player::Input(float timeStep, Tile* tiles[])
{
	WalkingLeft = false;
	WalkingRight = false;

	keyState = SDL_GetKeyboardState(NULL);
	//State machine
	switch(_state)
	{
		case state_idle:
			Xvel = 0;
			if(keyState[SDL_SCANCODE_A])
			{
				_state = state_walking;
			}
			else if(keyState[SDL_SCANCODE_D])
			{
				_state = state_walking;
			}
			if(keyState[SDL_SCANCODE_S])
			{
				isDucking = true;
				Yvel = walkingSpeed * timeStep;
				this->Move(vertical, tiles);
				this->Climb(down, tiles);
			}
			if(!keyState[SDL_SCANCODE_S])
			{
				isDucking = false;
			}
			if(keyState[SDL_SCANCODE_W])
			{
				this->GoTroughDoor(tiles);
				this->Climb(up, tiles);
			}
			if(!keyState[SDL_SCANCODE_W])
			{
				canEnterDoor = true;
			}
			if(keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT])
			{
				_state = state_running;
			}
			if(keyState[SDL_SCANCODE_L])
			{
				_state = state_attacking;
			}
			if(!keyState[SDL_SCANCODE_L])
			{
				isAttacking = false;
			}
			if(keyState[SDL_SCANCODE_K])
			{
				_state = state_blocking;
			}
			break;

		case state_walking:
			this->Move(horizontal, tiles);
			if(keyState[SDL_SCANCODE_A])
			{
				Xvel = -(walkingSpeed * timeStep);
				WalkingLeft = true;
				FacingRight = false;
				FacingLeft = true;
			}
			else if(keyState[SDL_SCANCODE_D])
			{

				Xvel = (walkingSpeed * timeStep);
				WalkingRight = true;
				FacingLeft = false;
				FacingRight = true;
			}
			else
			{
				_state = state_idle;
			}
			if(keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT])
			{
				_state = state_running;
			}
			if(keyState[SDL_SCANCODE_L])
			{
				_state = state_attacking;
			}
			if(keyState[SDL_SCANCODE_K])
			{
				_state = state_blocking;
			}
			break;

		case state_running:
			if(keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT])
			{
				if(Energy(NULL) > runEnergy && canRun)
				{
					if(keyState[SDL_SCANCODE_A])
					{
						Xvel = -(runningSpeed * timeStep);
						this->Move(horizontal, tiles);
						this->Energy(runEnergy);
						WalkingLeft = true;
						FacingRight = false;
						FacingLeft = true;
					}
					else if(keyState[SDL_SCANCODE_D])
					{
						Xvel = (runningSpeed * timeStep);
						this->Move(horizontal, tiles);
						this->Energy(runEnergy);
						WalkingRight = true;
						FacingLeft = false;
						FacingRight = true;
					}
					if(keyState[SDL_SCANCODE_SPACE])
					{
						_state = state_jumping;
					}
					isRunning = true;
				}
				else
				{
					canRun = false;
					if(keyState[SDL_SCANCODE_A])
					{
						Xvel = -(walkingSpeed * timeStep);
						this->Move(horizontal, tiles);
						this->Energy(runEnergy);
						WalkingLeft = true;
						FacingRight = false;
						FacingLeft = true;
					}
					else if(keyState[SDL_SCANCODE_D])
					{
						Xvel = (walkingSpeed * timeStep);
						this->Move(horizontal, tiles);
						this->Energy(runEnergy);
						WalkingRight = true;
						FacingLeft = false;
						FacingRight = true;
					}
					else
					{
						isRunning = false;
						canRun = false;
					}
				}
			}
			else
			{
				isRunning = false;
				canRun = true;
				_state = state_idle;
			}
			break;
			
		case state_jumping:
			if(keyState[SDL_SCANCODE_SPACE])
			{
				this->Jump(tiles);
			}
			else
			{
				_state = state_idle;
			}

			break;
			
		case state_climbing:
			if(keyState[SDL_SCANCODE_W])
			{
				Yvel = -(walkingSpeed * timeStep);
				this->Move(vertical, tiles);
				this->Climb(up, tiles);
			}
			else if(keyState[SDL_SCANCODE_S])
			{
				Yvel = (walkingSpeed * timeStep);
				this->Move(vertical, tiles);
				this->Climb(down, tiles);
			}
			else if(keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_D])
			{
				isClimbing = false;
				_state = state_idle;
			}
			break;
			
		case state_attacking:
			if(keyState[SDL_SCANCODE_L])
			{
				attack = true;
				this->Attack();
			}
			else
			{
				attack = false;
				this->Attack();
			}
			break;
			
		case state_blocking:
			if(keyState[SDL_SCANCODE_K])
			{
				block = true;
				this->Block();
			}
			else
			{
				block = false;
				this->Block();
			}
			break;
	}
}

void Player::Falling(float timeStep, Tile* tiles[])
{
	if(!isClimbing && !isJumping)
	{
		_PlayerBox.y += (GRAVITY * timeStep);
		if(pPhysics.Gravity_Box(timeStep, _PlayerBox, tiles))
		{
			_PlayerBox.y -= (GRAVITY * timeStep);
			isFalling = false;
		}
		else
		{
			isFalling = true;
		}
		if(!isFalling)
		{
			// Hyper gravity to keep the player grounded
			if(!pCollision.Stick_Rect(timeStep, bottomCollisionBox, tiles))
			{
				_PlayerBox.y = pPhysics.StickToFloor_Box(_PlayerBox, bottomCollisionBox, tiles);
			}
		}
	}	
}
// -------------------------------------------------//
// ------------NEEDS WORK, IS OK FOR NOW------------//
// -------------------------------------------------//
void Player::Jump(Tile* tiles[])
{
	if(canJump)
	{
		if(jumpingSpeed > GRAVITY)
		{
			Yvel = -jumpingSpeed;
			isClimbing = false;
			this->Energy(jumpEnergy);
			this->Move(jump, tiles);
			jumpingSpeed --;
		}
		else
		{
			jumpCount = 0;
			jumpingSpeed = jumpHeight + GRAVITY;
			_state = state_walking;
		}
	}
}

void Player::Climb(int Movement, Tile* tiles[])
{
	if(pCollision.Var_Rect(vertCenterCollisionBox, tiles, TILE_LADDER) || pCollision.Var_Rect(vertCenterCollisionBox, tiles, TILE_LADDER_TOP))
	{
		if(Movement == up || down)
		{
			_state = state_climbing;
			_PlayerBox.y += Yvel;
			isClimbing = true;
			isFalling = false;
			// Stick to center of ladder
			_PlayerBox.x = (((int)_PlayerBox.x + ((int)_PlayerBox.w/2))/TILE_SIZE)*TILE_SIZE;
			if(_PlayerBox.y < 0 || _PlayerBox.y + _PlayerBox.h > LEVEL_HEIGHT*TILE_SIZE ||  pCollision.Wall_Box(_PlayerBox, tiles))
			{
				_PlayerBox.y -= Yvel;
			}
		}
	}
	else
	{
		isClimbing = false;
	}
}

void Player::GoTroughDoor(Tile* tiles[])
{
	if(pCollision.Var_Rect(vertCenterCollisionBox, tiles, TILE_DOOR))
	{
		if(canEnterDoor)
		{
			pDoors.ConnectionBox(&_PlayerBox, NULL);
			canEnterDoor = false;
		}
	}
}

void Player::Attack()
{
	if(attack)
	{
		if(Energy(NULL) > attackEnergy)
		{
			if(FacingLeft)
			{
				SwordBox = {_PlayerBox.x - TILE_SIZE, _PlayerBox.y + TILE_SIZE, TILE_SIZE, 10};
			}
			else if(FacingRight)
			{
				SwordBox = {_PlayerBox.x + _PlayerBox.w, _PlayerBox.y + TILE_SIZE, TILE_SIZE, 10};
			}
			if(!isAttacking)
			{
				Energy(attackEnergy);
				isAttacking = true;
				energyRecover = false;
			}
		}
		else
		{
			if(FacingLeft)
			{
				SwordBox = {_PlayerBox.x - 10, _PlayerBox.y + TILE_SIZE, 10, 10};
			}
			else if(FacingRight)
			{
				SwordBox = {_PlayerBox.x + this->_PlayerBox.w, _PlayerBox.y + TILE_SIZE, 10, 10};
			}
		}
	}
	else
	{
		SwordBox = {NULL, NULL, NULL, NULL};
		isAttacking = false;
		_state = state_idle;
		energyRecover = true;
	}
}

void Player::Block()
{
	if(block)
	{
		if(Energy(NULL) > blockEnergy)
		{
			if(FacingLeft)
			{
				ShieldBox = {_PlayerBox.x - 10, _PlayerBox.y, 10, _PlayerBox.h};
			}
			else if(FacingRight)
			{
				ShieldBox = {_PlayerBox.x + this->_PlayerBox.w, _PlayerBox.y, 10, _PlayerBox.h};
			}
			if(!isBlocking)
			{
				Energy(blockEnergy);
				isBlocking = true;
				energyRecover = false;
			}
		}
		else
		{
			if(FacingLeft)
			{
				ShieldBox = {_PlayerBox.x - 2, _PlayerBox.y, 2, _PlayerBox.h};
			}
			if(FacingRight)
			{
				ShieldBox = {_PlayerBox.x+ this->_PlayerBox.w, _PlayerBox.y, 2, _PlayerBox.h};
			}
		}
	}
	else
	{
		ShieldBox = {NULL, NULL, NULL, NULL};
		isBlocking = false;
		_state = state_idle;
		energyRecover = true;
	}
}

void Player::Move(int Movement, Tile* tiles[])
{
	if(!isAttacking)
	{
		// Horizontal movement
		if(Movement == horizontal || Movement == jump)
		{
			_PlayerBox.x += Xvel;
		}
		// Horizontal collision handling
		if(_PlayerBox.x < 0 || _PlayerBox.x + _PlayerBox.w > LEVEL_WIDTH*TILE_SIZE || pCollision.Wall_Box(_PlayerBox, tiles))
		{
			_PlayerBox.x -= Xvel;
		}
		// Horizontal Slope collision handling
		if(pCollision.Slope_45_Left_Box(_PlayerBox, tiles))//[/]
		{
			if((TILE_SIZE - (((int)_PlayerBox.x) + ((int)_PlayerBox.w-1)) % TILE_SIZE) == 1)
			{
				// compesate for colliding in to next tile becoude of the playerRect.w -1
				_PlayerBox.y = ((TILE_SIZE - (((int)_PlayerBox.x) + ((int)_PlayerBox.w-1)) % TILE_SIZE) + (((int)_PlayerBox.y-1)/ TILE_SIZE)*TILE_SIZE) -1;
			}
			else if(isRunning && TILE_SIZE - (((int)_PlayerBox.x + (int)_PlayerBox.w-1)) % TILE_SIZE <= runningSpeed)
			{
				// composate for collidoing in to next tiles becouse of running
				_PlayerBox.y = ((TILE_SIZE - (((int)_PlayerBox.x) + ((int)_PlayerBox.w-1)) % TILE_SIZE) + (((int)_PlayerBox.y-1)/ TILE_SIZE)*TILE_SIZE) -(Xvel);
			}
			else if(TILE_SIZE - ((int)_PlayerBox.x + (int)_PlayerBox.w-1) % TILE_SIZE <= walkingSpeed)
			{
				// composate for collidoing in to next tiles of decelerating
				_PlayerBox.y = ((TILE_SIZE - (((int)_PlayerBox.x) + ((int)_PlayerBox.w-1)) % TILE_SIZE) + (((int)_PlayerBox.y-1)/ TILE_SIZE)*TILE_SIZE) -(Xvel);	
			}
			else
			{
				_PlayerBox.y = (TILE_SIZE - (((int)_PlayerBox.x) + ((int)_PlayerBox.w-1)) % TILE_SIZE) + (((int)_PlayerBox.y-1)/ TILE_SIZE)*TILE_SIZE;
			}
		}
		if(pCollision.Slope_45_Right_Box(_PlayerBox, tiles))//[\]
		{
			if(isRunning && (((int)_PlayerBox.x) % TILE_SIZE) <= runningSpeed)
			{
				// composate for collidoing in to next tiles becouse of running
				_PlayerBox.y = (((int)_PlayerBox.x) % TILE_SIZE) + (((int)_PlayerBox.y-1)/ TILE_SIZE)*TILE_SIZE -(Xvel);
			}
			else if(((int)_PlayerBox.x % TILE_SIZE) <= walkingSpeed)
			{
				// composate for collidoing in to next tiles of decelerating
				_PlayerBox.y = (((int)_PlayerBox.x) % TILE_SIZE) + (((int)_PlayerBox.y-1)/ TILE_SIZE)*TILE_SIZE -(Xvel);
			}
			else
			{
				_PlayerBox.y = (((int)_PlayerBox.x) % TILE_SIZE) + (((int)_PlayerBox.y-1)/ TILE_SIZE)*TILE_SIZE;
			}
		}
		// Vertical movement
		if(Movement == vertical  || Movement == jump)
			_PlayerBox.y += Yvel;
		// Vertical collision handling
		if(_PlayerBox.y < 0 || _PlayerBox.y + _PlayerBox.h > LEVEL_HEIGHT*TILE_SIZE || 
			pCollision.Wall_Box(_PlayerBox, tiles) ||
			pCollision.Slope_45_Right_Box(_PlayerBox, tiles) ||
			pCollision.Slope_45_Left_Box(_PlayerBox, tiles)
		  )
			_PlayerBox.y -= Yvel;
	}
}

int Player::Health()
{
	if(health <=0)
	{
		health =0;
	}
	return maxHealth;
}

int Player::Energy(int action)
{
	if(energy <= 0)
	{
		energy = 0;
	}
	if(_state == state_idle || _state == state_walking)
	{
		if(energyRecover && action == NULL && energy < maxEnergy)
		{
			energy ++;
		}
	}
	energy = energy - action;
	return energy;
}

void Player::Render(float timeStep, SDL_Renderer* Renderer, SDL_Rect* camera)
{
	// cout << frameCounter << endl;
	frameCounter += frameSpeed * timeStep;
	if(frameCounter > frameSwitch)
	{
		// Walking Animation
		if(WalkingLeft)
		{
			frame --;
			frameCounter = 0;
			if(frame < EndFrameLeft || frame > StartFrameLeft)
			{
				frame = StartFrameLeft;
			}
		}
		else
		{
			//Idle frame left
			if(FacingLeft)
			{
				frame = IdleFrameLeft;
			}
		}
		if(WalkingRight)
		{
			frame ++;
			frameCounter = 0;
			if(frame  > EndFrameRight || frame < StartFrameRight)
			{
				frame = StartFrameRight;
			}
		}
		else
		{
			//Idle frame right
			if(FacingRight)
			{
				frame = IdleFrameRight;
			}
		}
	}
	//Show collsiion box
	SDL_SetRenderDrawColor(Renderer, 0xff, 0x00, 0x00, 0xff);
	playerBox = {_PlayerBox.x - camera->x, _PlayerBox.y - camera->y, _PlayerBox.w, _PlayerBox.h};
	SDL_RenderFillRect(Renderer, &playerBox);
	
	//Create New Rectangle for sword for the camera compisation
	Sword = {SwordBox.x - camera->x, SwordBox.y - camera->y, SwordBox.w, SwordBox.h};
	SDL_RenderFillRect(Renderer, &Sword);
	
	HealthBar = {10, 10, this->Health(), 10};
	StaminBar = {10, 25, this->Energy(NULL), 10};
	SDL_RenderFillRect(Renderer, &HealthBar);
	SDL_SetRenderDrawColor(Renderer, 0x00, 0xff, 0x00, 0xFF );
	SDL_RenderFillRect(Renderer, &StaminBar);
	//Render Frame
	SpriteSheetTexture.Render(Renderer, (int)_PlayerBox.x - camera->x, (int)_PlayerBox.y - camera->y, &PlayerClips[frame]);
	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0xff, 0xff);
	//Create New Rectangle for shield for the camera compisation
	Shield = {ShieldBox.x - camera->x, ShieldBox.y - camera->y, ShieldBox.w, ShieldBox.h};
	SDL_RenderFillRect(Renderer, &Shield);
}

void Player::Update()
{
	// initiolize bottomCollisionBox
	bottomCollisionBox = {_PlayerBox.x, (_PlayerBox.y + _PlayerBox.h), _PlayerBox.w, 1};
	// initialize vertCenterCollisionBox
	vertCenterCollisionBox = {_PlayerBox.x + (_PlayerBox.w/2), _PlayerBox.y, 2, _PlayerBox.h+1};
}

void Player::Cleanup()
{
	SpriteSheetTexture.Free();
}