#pragma once

#include "GameObject.h"
#include "MathUtils.h"

class Map : public GameObject
{
public:
	Map();
	void Initialize(SDL_Renderer * renderer, char* file);
	void Update(float dt);
	void Draw(SDL_Renderer * renderer, float dt);
	bool checkCollision(Vector2);

	bool blockPos[25][25];
};