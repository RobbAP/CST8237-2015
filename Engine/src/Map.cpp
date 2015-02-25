#include "Map.h"
#include <random>
#include <ctime>

Map::Map() : GameObject()
{

}

void Map::Initialize(SDL_Renderer* renderer, char* file)
{
	int isWall = 0;
	srand(time(NULL));

	// Vertical Squares
	for (int i = 0; i < 25; ++i)
	{
		// Horizontal squares
		for (int j = 0; j < 25; ++j)
		{
			// Generate a random number to check if a block is a wall or not
			isWall = rand() % 5;

			// Add walls all around the map
			if (i == 0 || j == 0 || i == 24 || j == 24)
			{
				blockPos[i][j] = true;
			}
			// Remove walls touching the borders to make traversing the map better
			else if (i == 1 || j == 1 || i == 23 || j == 23)
			{
				blockPos[i][j] = false;
			}
			else if (isWall == 3)
			{
				blockPos[i][j] = true;
			}
			else
			{
				blockPos[i][j] = false;
			}
		}
	}
}

void Map::Update(float dt)
{

}

void Map::Draw(SDL_Renderer * renderer, float dt)
{
	for (int vertical = 0; vertical < 25; ++vertical)
	{
		for (int horizontal = 0; horizontal < 25; ++horizontal)
		{
			SDL_Rect tempSquare;

			tempSquare.x = horizontal * 32;
			tempSquare.y = vertical * 32;
			tempSquare.h = 32;
			tempSquare.w = 32;

			if (blockPos[vertical][horizontal])
			{
				SDL_SetRenderDrawColor(renderer, 175, 200, 150, 255);
				SDL_RenderFillRect(renderer, &tempSquare);
			}

			else
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
				SDL_RenderFillRect(renderer, &tempSquare);
			}
		}
	}
}

bool Map::checkCollision(Vector2 point)
{
	for (int v = 0; v < 25; v++)
	{
		for (int h = 0; h < 25; h++)
		{
			if (blockPos[v][h] == true)
			{
				// Check if the point is touching one of the walls
				if (point.y <= ((v * 32) + 32) && 
					point.x <= ((h * 32) + 32) &&
					point.y >= (v * 32) && 
					point.x >= (h * 32))
					return true;
			}
		}
	}
	return false;
}