#pragma once // Preprocessor directive to ensure that this header will only be included once. -- Generally used on Windows

#include "MathUtils.h"
#include "Player.h"
#include "Timer.h"
#include "Map.h"
#include "Bullet.h"
#include <vector>

// Forward declaring our renderer and window.
// Because we're using them as pointers, we don't need to know their size
// at compile time to define this class.
struct SDL_Renderer;
struct SDL_Window;
class GameObject;

class GameEngine
{
public:
  /**
   * Creates a GameEngine instance
   * @return The new GameEngine instance, NULL if no instance could be created.
   */
  static GameEngine* CreateInstance();

  void Initialize();
  void Shutdown();
  void Update();
  void Draw();
  ~GameEngine();

protected:
  GameEngine();
  virtual void InitializeImpl() = 0;
  virtual void UpdateImpl(float dt) = 0;
  virtual void DrawImpl(SDL_Renderer *renderer, float dt) = 0;
  static GameEngine *_instance;
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  Timer _engineTimer;
  SDL_Rect playerOnePos;
  SDL_Rect playerTwoPos;
  SDL_Texture* _blueTank;
  SDL_Texture* _greenTank;
  Bullet* _playerOneAmmo[10];
  Bullet* _playerTwoAmmo[10];

  std::vector<GameObject *> _objects;

  float _oldTime, _currentTime, _deltaTime;
  float _deathTime;
};