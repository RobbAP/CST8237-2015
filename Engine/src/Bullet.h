#pragma once

#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet();
	void Initialize(SDL_Renderer* renderer, char *file);
	void Update(float dt);
	void Draw(SDL_Renderer *renderer, float dt);
	void Shot(Vector2 startLocation, int direction);
	Vector2 Bullet::Move(Vector2 pos, float dir, float speed);
	Vector2 GetLocation();
	int GetLife();
	float GetDirection();
	void SetDirection(float);
	Vector2 lookAhead(float);
	void Bounce();
	void Destroy();
protected:
	float _direction;
	float _speed;
	Vector2 _location;
	int _life;
};