#include "Game.h"
#include <GameObject.h>
#include <SDL.h>
#include <math.h>
#include <SDL_image.h>
#include <Box2D\Box2D.h>

// Initializing our static member pointer.
GameEngine* GameEngine::_instance = nullptr;

GameEngine* GameEngine::CreateInstance()
{
  if (_instance == nullptr)
  {
    _instance = new Game();
  }
  return _instance;
}

Game::Game() : GameEngine()
{

}

Game::~Game()
{
}

void Game::InitializeImpl()
{
  SDL_SetWindowTitle(_window, "Tanks");

  for (auto itr = _objects.begin(); itr != _objects.end(); itr++)
  {
    (*itr)->Initialize(_renderer);
  }

  // Box2d vector 2 for gravity as a constant
  b2Vec2 gravity(0.0f, 1.0f);

  // Initialize our Box2D World
  _world = new b2World(gravity);
  b2BodyDef boxBodyDef;

  /* 3 types of physics bodies in box2D - Dynamic, Static, Kinematic 
   * Dynamic - Bodies that are affected by 
   * Static - Bodies that are created and remain stationary but other objects can be affected by them
   * Kinematic - 0 mass object moved for us - Not worried about this right now 
   */
  boxBodyDef.type = b2_dynamicBody;

  /* Pass in a reference to our body definition */
  _boxBody = _world->CreateBody(&boxBodyDef);

  /* Set the position the body will start at */
  b2Vec2 boxPosition(250.0, 0.0);

  /* Set the body's transform to the position previously created */
  _boxBody->SetTransform(boxPosition, 0.0f);

  /* Define a shape for our body */
  b2PolygonShape boxShape;

  /* Define the box's shape as a 5x5 square */
  boxShape.SetAsBox(5, 5);

  /*  */
  _boxFixture = _boxBody->CreateFixture(&boxShape, 0.0f);

}

void Game::UpdateImpl(float dt)
{
  SDL_Event evt;
  SDL_PollEvent(&evt);

  for (auto itr = _objects.begin(); itr != _objects.end(); itr++)
  {
    (*itr)->Update(dt);
  }
}

void Game::DrawImpl(SDL_Renderer *renderer, float dt)
{
  std::vector<GameObject *> renderOrder;
  CalculateDrawOrder(renderOrder);

  for (auto itr = renderOrder.begin(); itr != renderOrder.end(); itr++)
  {
    (*itr)->Draw(renderer, dt);
  }
}

void Game::CalculateDrawOrder(std::vector<GameObject *>& drawOrder)
{
  // SUPER HACK GARBAGE ALGO.
  drawOrder.clear();

  auto objectsCopy = _objects;
  auto farthestEntry = objectsCopy.begin();
  while (objectsCopy.size() > 0)
  {
    bool entryFound = true;
    for (auto itr = objectsCopy.begin(); itr != objectsCopy.end(); itr++)
    {
      if (farthestEntry != itr)
      {
        if ((*itr)->GetTransform().position.y < (*farthestEntry)->GetTransform().position.y)
        {
          entryFound = false;
          farthestEntry = itr;
          break;
        }
      }
    }

    if (entryFound)
    {
      GameObject *farthest = *farthestEntry;

      drawOrder.push_back(farthest);
      objectsCopy.erase(farthestEntry);
      farthestEntry = objectsCopy.begin();
    }
  }
}
