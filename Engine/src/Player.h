#pragma once

#include "GameObject.h"
#include "MathUtils.h"

#define WIDTH 10
#define HEIGHT 10

class Player : public GameObject
{
public:
	Player();
	void Initialize(SDL_Renderer* renderer, char *file);
	void Update(float dt);
	void Draw(SDL_Renderer *renderer, float dt);

	Vector2 Player::Move(Vector2 playerPos, float dir, float speed);

	void SetPosition(Vector2 pos);
	Vector2 GetPosition();

	void SetRotation(int degrees);
	int GetRotation();

	void SetSpeed(int speed);
	int GetSpeed();

	int getScore();

	void Kill();
	void Spawn();
	void NudgePlayer(float dt);
	bool CheckCollision(Vector2 playerPos);
	bool isAlive();
	void incrementScore();
	~Player(); 

protected:
	int _rotationDegrees;
	float _rotationRadians;
	int _speed;
	float _score;
	float _rateOfAcc;

	Vector2 _ship;
	Vector2 _shipOffset;

	SDL_Rect tank;
	SDL_Point tankPos;

	SDL_Texture* tankTexture;

	bool _alive;
};
