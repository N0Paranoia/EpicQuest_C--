#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include "Tile.h"
#include "Mobs.h"
#include <iostream>

using namespace std;

class Player
{
private:
	enum State
	{
		state_idle, // 0
		state_jumping, // 1
		state_walking, // 2
		state_running, // 3
		state_attacking, //4
		state_blocking, // 5
		state_climbing // 6
	};

	enum Movement
	{
		horizontal,
		vertical,
		left,
		right,
		up,
		down,
		jump
	};

	const Uint8* keyState;

	int walkingSpeed;
	int runningSpeed;
	int jumpingSpeed;

	int jumpCount;
	int jumpHeight;
	int climbingSpeed;

	bool WalkingLeft;
	bool WalkingRight;

	bool isRunning;
	bool canRun;
	bool isFalling;
	bool canJump;
	bool isJumping;
	bool isDucking;

	bool canEnterDoor;
	bool isClimbing;

	bool attack;
	bool isAttacking;
	bool block;
	bool isBlocking;

	int runEnergy;
	int jumpEnergy;
	int attackEnergy;
	int blockEnergy;

	int maxEnergy;
	int energy;
	bool energyRecover;
	int maxHealth;
	int currentHealth;
	int health;

	int frame;
	int StartFrameLeft;
	int EndFrameLeft;
	int StartFrameRight;
	int EndFrameRight;
	int IdleFrameLeft;
	int IdleFrameRight;
	int frameCounter;
	int frameSpeed;
	int frameSwitch;

	SDL_Rect PlayerClips[18];

	SDL_Rect HealthBar;
	SDL_Rect StaminBar;
	SDL_Rect bottomCollisionBox;
public:
	bool FacingLeft;
	bool FacingRight;
	int _state;
	int Xvel, Yvel;
	//Collision box
	SDL_Rect playerRect;
	SDL_Rect vertCenterCollisionBox;
	SDL_Rect playerBox;
	SDL_Rect SwordBox;
	SDL_Rect ShieldBox;

	SDL_Rect Shield;
	SDL_Rect Sword;

	Player();
	virtual ~Player();

	void Input(Tile* tiles[], Mobs* mobs[]);
	int LoadMedia(SDL_Renderer* Renderer);
	void Move(int Movement, Tile* tiles[]);
	void Attack(Mobs* mobs[]);
	void Block();
	void Jump(Tile* tiles[]);
	void Climb(int Movement, Tile* tiles[]);
	void Falling(Tile* tiles[]);
	void GoTroughDoor(Tile* tiles[]);
	int Health(int damage);
	int Energy(int action);
	void MobsCollision(Mobs* mobs[], int i);
	void Update(Mobs* mobs[]);
	void Render(SDL_Renderer* Renderer, SDL_Rect* camera);
	void Cleanup();

protected:
};

#endif // PLAYER_H
