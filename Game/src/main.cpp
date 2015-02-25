#include <iostream>
#include "Game.h"
#include <ctime>

using namespace std;

int main(int argc, char** argv)
{
  GameEngine *engine = GameEngine::CreateInstance();
  engine->Initialize();

  srand(time(NULL));

  while(true)
  {
    engine->Update();
    engine->Draw();
  }

  engine->Shutdown();

  return 0;
}