#include "Player.h"
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <stdio.h>

Player::Player() : GameObject()
{
	_transform.position = { 400.0f, 400.0f, 0.0f };
}

Player::~Player()
{
}

// Initializes the spaceships attributes and properties
void Player::Initialize()
{
	shoot = false;
	shootDown = true;
	hits = 0;
	rotationDegrees = 0.0f;
	rotationSpeed = 100.0f;
	velocity = { 0.0f, 0.0f };
	rateOfAcc = 15.0;
	friction = 0.9999f;
	ship.x = 320;
	ship.y = 320;
	endPointOffsetA = { 0, 15 };;
	initBullets();
	ship2 = { 320, 320, 30, 30 };
}

// Update the player's spaceship checking screen bounds, bullets fired, and rotation
void Player::Update(float dt)
{
	rotationDegrees += (rotationDegrees >= 360.0f ? -360.0f : 0);
	rotationRadians = MathUtils::ToRadians(rotationDegrees);

	// Handles player going out of the screen bounds
	if (ship2.y > 639)
		ship2.y = 0;
	if (ship2.y < 1)
		ship2.y = 640;
	if (ship2.x > 639)
		ship2.x = 0;
	if (ship2.x < 1)
		ship2.x = 640;

	// Update the players position based on their velocity
	ship2.x += (dt*velocity.x);
	ship2.y += (dt*velocity.y);

	// Fire
	if (shoot == true)
	{
		Fire();
	}

	// Update the bullets
	/*
	for (int j = 0; j < MAXBULLETS; j++)
	{
		if (bullet[j].ttl > 0)
			bullet[j].Update(dt);
	}
	*/

	/* Caps velocity to limit speed
	if (velocity.x > 50)
	velocity.x = 50;
	if (velocity.y > 50)
	velocity.y = 50;
	if (velocity.x < -50)
	velocity.x = -50;
	if (velocity.y < -50)
	velocity.y = -50;
	*/

}

// calculates new offsets based on players rotation and draws the spaceship
void Player::Draw(SDL_Renderer *renderer, float dt)
{
	rotatedOffsetA =
	{
		endPointOffsetA.x * cosf(rotationRadians) + endPointOffsetA.y * sinf(rotationRadians),
		endPointOffsetA.x * sinf(rotationRadians) - endPointOffsetA.y * cosf(rotationRadians)
	};

	rotatedOffsetB =
	{
		endPointOffsetB.x * cosf(rotationRadians) + endPointOffsetB.y * sinf(rotationRadians),
		endPointOffsetB.x * sinf(rotationRadians) - endPointOffsetB.y * cosf(rotationRadians)
	};

	rotatedOffsetC =
	{
		endPointOffsetC.x * cosf(rotationRadians) + endPointOffsetC.y * sinf(rotationRadians),
		endPointOffsetC.x * sinf(rotationRadians) - endPointOffsetC.y * cosf(rotationRadians)
	};

	// Calculate the new position for the spaceship
	transformedEndPointA = { ship2.x + rotatedOffsetA.x, ship2.y + rotatedOffsetA.y };
	transformedEndPointB = { ship2.x + rotatedOffsetB.x, ship2.y + rotatedOffsetB.y };
	transformedEndPointC = { ship2.x + rotatedOffsetC.x, ship2.y + rotatedOffsetC.y };

	// Draw the ship
	SDL_RenderDrawLine(renderer, transformedEndPointA.x, transformedEndPointA.y, transformedEndPointB.x, transformedEndPointB.y);
	SDL_RenderDrawLine(renderer, transformedEndPointB.x, transformedEndPointB.y, transformedEndPointC.x, transformedEndPointC.y);
	SDL_RenderDrawLine(renderer, transformedEndPointC.x, transformedEndPointC.y, transformedEndPointA.x, transformedEndPointA.y);

	// Redraw the bullets
	/*
	for (int j = 0; j < MAXBULLETS; j++)
	{
		if (bullet[j].ttl > 0)
			bullet[j].Draw(renderer, dt);
	}
	*/
}

// Fire's a bullet from the spaceship. array of bullets holds MAXBULLETS which is default 10.
void Player::Fire()
{
	// If the player pressed space to fire a bullet
	if (shoot == true)
	{
		// If the shoot button has been released
		if (shootDown == true)
		{
			shootDown = false;
			int index = -1;
			// Check if there is an empty bullet slot
			/*
			for (int i = 0; i < MAXBULLETS; i++)
			{
				// Found an empty bullet slot
				if (bullet[i].ttl <= 0)
				{
					index = i;
					break;
				}
			}
			// No free slots for bullets found
			if (index == -1)
				return;

			bullet[index].setOrigin(ship);
			bullet[index].setRotation(rotationRadians);
			bullet[index].Initialize();
			*/
		}
	}
}

// Initializes
void Player::initBullets()
{
	/*
	for (int i = 0; i < MAXBULLETS; i++)
	{
		bullet[i].ttl = 0;
		bullet[i].bullet = { 0, 0 };
	}
	*/
}