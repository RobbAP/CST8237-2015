#pragma once

#include "GameObject.h"
#include "MathUtils.h"

struct spaceShip
{
	Vector2 midPoint;
};

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Initialize();

	void Update(float dt);
	void Draw(SDL_Renderer *renderer, float dt);

	void Fire();
	void initBullets();

	// Handles bullet fire on release instead of press
	bool shoot;
	bool shootDown;

	// Rotation angle
	float rotationDegrees;
	// Rotation speed
	float rotationSpeed;
	// After calculation
	float rotationRadians;

	// Ship's mid point
	Vector2 ship;

	// Ship's velocity
	Vector2 velocity;

	SDL_Rect ship2;

	// Points to draw a triangular ship
	Vector2 endPointOffsetA;
	Vector2 endPointOffsetB;
	Vector2 endPointOffsetC;

	// Calculated in draw to rotate spaceship's points
	Vector2 rotatedOffsetA;
	Vector2 rotatedOffsetB;
	Vector2 rotatedOffsetC;

	// Calculated in update to draw spaceship's new position
	Vector2 transformedEndPointA;
	Vector2 transformedEndPointB;
	Vector2 transformedEndPointC;

	// Friction slows the spaceship down
	float friction;

	// Used to calculate how much faster the ship gets while thrusting
	float rateOfAcc;

	// Number of asteroids hit
	int hits;

	// Array for the bullets default to 10
	//Bullet bullet[MAXBULLETS];
};
