#pragma once

#include <GameEngine.h>

union SDL_Event;
struct SDL_Texture;

class b2World;
class b2Body;
class b2Fixture;

class Game: public GameEngine
{
  friend class GameEngine;

public:
  ~Game();

protected:
  Game();

  void InitializeImpl();
  void UpdateImpl(float dt);
  void DrawImpl(SDL_Renderer *renderer, float dt);

  void Reset();
  void CalculateDrawOrder(std::vector<GameObject *>& drawOrder);

  b2World *_world;
  b2Body *_boxBody;
  b2Fixture *_boxFixture;
};