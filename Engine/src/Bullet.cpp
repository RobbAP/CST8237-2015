#include "Bullet.h"
#include "Map.h"
#include <SDL.h>
#include <random>
#include <cmath>

Bullet::Bullet() : GameObject()
{
}

void Bullet::Initialize(SDL_Renderer* renderer, char *file)
{
	_direction = 0;
	_location = { 0, 0 };
	_speed = 100;
	_life = 3;
}

void Bullet::Update(float dt)
{
	_location = Move(_location, _direction, (_speed * dt));
}

void Bullet::Draw(SDL_Renderer *renderer, float dt)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	// Clear the renderer with the current draw colour.
	SDL_RenderDrawPoint(renderer, _location.x, _location.y);
}

void Bullet::Shot(Vector2 startLocation, int direction)
{
	_location = { startLocation.x, startLocation.y };
	_direction = direction;
}

Vector2 Bullet::GetLocation()
{
	return _location;
}

int Bullet::GetLife()
{
	return _life;
}

float Bullet::GetDirection()
{
	return _direction;
}

void Bullet::SetDirection(float dir)
{
	_direction = dir;
}

Vector2 Bullet::lookAhead(float dt)
{
	return Move(_location, _direction, (_speed * dt));
}

void Bullet::Bounce()
{
	_life--;

	// Change the bullets direction if necissary
	while (_direction > 360)
	{
		_direction = _direction - 360;
	}

	if (_direction < 180)
		_direction = 180 - _direction;
	else
		_direction = 360 - _direction;
}

void Bullet::Destroy()
{
	_life = 0;
	_location = { -1, -1 };
}

/*
* Function name	-	Move()
* Description	-
* Return value	-	a Vector2 containing the new location of the ship
*/
Vector2 Bullet::Move(Vector2 pos, float dir, float speed)
{
	float rotationRadians = MathUtils::ToRadians(dir);

	float oldX = pos.x;
	float oldY = pos.y;

	float newX = sin(-1 * rotationRadians);
	float newY = cos(-1 * rotationRadians);

	float magnitude = sqrt((newX * newX) + (newY * newY));
	float pointX = newX / magnitude;
	float pointY = newY / magnitude;

	return{ (oldX + (pointX * speed)), (oldY + (pointY * speed)) };
}