#include "Player.h"
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <stdio.h>

/*
* Function name -
* Description   -
* Return value	-
*/
Player::Player() : GameObject()
{
}

/*
* Function name - Initialize()
* Description   - Initializes a player's tank
* Return value	- none
*/
void Player::Initialize(SDL_Renderer* renderer, char* file)
{
	int h, w = 20;

	tankTexture = IMG_LoadTexture(renderer, file);
	if (tankTexture == NULL)
	{
		printf(SDL_GetError());
		printf("\n");
	}

	if (SDL_QueryTexture(tankTexture, NULL, NULL, &h, &w))
	{
		printf(SDL_GetError());
		printf("\n");
	}

	_shipOffset = { 0, 0 };
	_rotationDegrees = 90.0f;
	_speed = 0;
	_score = 0;
	_ship = { 320, 320 };
}

/*
* Function name -
* Description   -
* Return value	-
*/
void Player::Update(float dt)
{
	//Reset rotation if it exceeds 360 degrees
	_rotationDegrees += (_rotationDegrees >= 360.0f ? -360.0f : 0);

	_ship = Move(_ship, _rotationDegrees, (dt * _speed) * -1);
}

/*
* Function name -
* Description   -
* Return value	-
*/
void Player::Draw(SDL_Renderer *renderer, float dt)
{
	tankPos = { 10, 15 };

	tank.x = (_ship.x - 20);
	tank.y = (_ship.y - 30);

	tank.w = 20;
	tank.h = 30;

	SDL_RenderCopyEx(renderer, tankTexture, NULL, &tank, _rotationDegrees, &tankPos, SDL_FLIP_NONE);
}

/*
 * Function name -	isAlive()
 * Description	 -	checks if a player is currently alive
 * Return value	 -	true if a player is alive, false otherwise
 */
bool Player::isAlive()
{
	return _alive;
}

/*
* Function name -
* Description   -
* Return value	-
*/
int Player::getScore()
{
	return _score;
}

/*
* Function name -
* Description   -
* Return value	-
*/
void Player::Kill()
{
	_alive = false;
}

/*
* Function name -
* Description   -
* Return value	-
*/
void Player::Spawn()
{
	_alive = true;
}

/*
* Function name -
* Description   -
* Return value	-
*/
void Player::incrementScore()
{
	_score += 10;
}

/*
* Function name -
* Description   -
* Return value	-
*/
void Player::SetRotation(int degrees)
{
	
	_rotationDegrees = degrees;
}

/*
* Function name -
* Description   -
* Return value	-
*/
int Player::GetRotation()
{
	return _rotationDegrees;
}

/*
* Function name -
* Description   -
* Return value	-
*/
void Player::SetSpeed(int speed)
{
	_speed = speed;
}

/*
* Function name -
* Description   -
* Return value	-
*/
int Player::GetSpeed()
{
	return _speed;
}

/*
* Function name -
* Description   -
* Return value	-
*/
bool Player::CheckCollision(Vector2 playerPos)
{
	/*Convert direction to radians.*/
	_rotationRadians = MathUtils::ToRadians(_rotationDegrees);

	/*Calculate new point based on center.*/
	float newPointX = (cos(_rotationRadians) * _ship.x) - (sin(_rotationRadians) * _ship.y);
	float newPointY = (sin(_rotationRadians) * _ship.x) + (cos(_rotationRadians) * _ship.y);

	newPointX = _ship.x + newPointX;
	newPointY = _ship.y + newPointY;

	/*Check if point is in collision range.*/
	if (playerPos.x <= (newPointX + 8) && playerPos.x >= (newPointX - 8) &&
		playerPos.y <= (newPointY + 8) && playerPos.y >= (newPointY - 8))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
* Function name - SetPosition()
* Description   - Sets the position of a player to a given point
* Return value	- none
*/
void Player::SetPosition(Vector2 pos)
{
	_ship = pos;
}

/*
* Function name - GetPosition()
* Description   - Returns the position of a player
* Return value	- A Vector2 representing a players position in the game
*/
Vector2 Player::GetPosition()
{
	return _ship;
}

/*
* Function name	-	Move()
* Description	-	
* Return value	-	a Vector2 containing the new location of the ship
*/
Vector2 Player::Move(Vector2 playerPos, float dir, float speed)
{
	float rotationRadians = MathUtils::ToRadians(dir);

	float oldX = playerPos.x;
	float oldY = playerPos.y;

	float newX = sin(-1 * rotationRadians);
	float newY = cos(-1 * rotationRadians);

	float magnitude = sqrt((newX * newX) + (newY * newY));
	float pointX = newX / magnitude;
	float pointY = newY / magnitude;

	return { (oldX + (pointX * speed)), (oldY + (pointY * speed)) };
}

/*
* Function name	-	NudgePlayer()
* Description	-	Nudges the player if they collide with something
* Return value	-	none
*/
void Player::NudgePlayer(float dt)
{
	_ship = Move(_ship, _rotationDegrees, ((dt * _speed) * 25));
	_speed = 0;
}