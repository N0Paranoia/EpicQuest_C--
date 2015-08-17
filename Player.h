#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include "Constants.h"
#include "Tile.h"
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
		bool FacingLeft;
		bool FacingRight;
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
		int health;

		int frame;
		int StartFrameLeft;
		int EndFrameLeft;
		int StartFrameRight;
		int EndFrameRight;
		int IdleFrameLeft;
		int IdleFrameRight;
		float frameCounter;
		float frameSpeed;
		float frameSwitch;

		SDL_Rect PlayerClips[18];
		SDL_Rect ShieldBox;
		SDL_Rect Shield;
		SDL_Rect SwordBox;
		SDL_Rect Sword;
		SDL_Rect HealthBar;
		SDL_Rect StaminBar;
	public:
		int playerInt;

		int _state;
		float Xvel, Yvel;

		//Collision box
		Box _PlayerBox;
		
		SDL_Rect bottomCollisionBox;
		SDL_Rect vertCenterCollisionBox;
		SDL_Rect playerBox;

		Player();
		virtual ~Player();
		//void Event(SDL_Event* event);
		void Input(float timeStep, Tile* tiles[]);
		int LoadMedia(SDL_Renderer* Renderer);

		void Move(float timeStep, int Movement, Tile* tiles[]);
		void Attack();
		void Block();
		void Jump(float timeStep, Tile* tiles[]);
		void Climb(int Movement, Tile* tiles[]);
		void Falling(float timeStep, Tile* tiles[]);
		void GoTroughDoor(Tile* tiles[]);
		int Health();
		int Energy(int action);
		void Update();
		void Render(float timeStep, SDL_Renderer* Renderer, SDL_Rect* camera);
		void Cleanup();

	protected:
};

#endif // PLAYER_H
