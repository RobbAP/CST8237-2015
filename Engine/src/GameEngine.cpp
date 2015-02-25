#include "GameEngine.h"
#include <SDL.h>
#include <SDL_image.h>

Player *playerOne = new Player();
Player *playerTwo = new Player();
Map *map = new Map();

char* tankOne = "../Engine/blue_tank.png";
char* tankTwo = "../Engine/green_tank.png";

GameEngine::GameEngine()
{

}

GameEngine::~GameEngine()
{

}

void GameEngine::Initialize()
{
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER);

  _window = SDL_CreateWindow("Engine",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    800, 800,
    SDL_WINDOW_SHOWN);

  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

  IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);

  map->Initialize(_renderer, "");

  playerOne->Initialize(_renderer, tankOne);
  playerTwo->Initialize(_renderer, tankTwo);
  playerTwo->SetRotation(270.0);

  playerOnePos = { 30, 30 };
  playerTwoPos = { 30, 30 };

  playerOne->SetPosition({ 55, 400 });
  playerTwo->SetPosition({ 755, 400 });

  for (int i = 0; i < 10; i++)
  {
	  _playerOneAmmo[i] = NULL;
	  _playerTwoAmmo[i] = NULL;
  }

  /* Get the time at the beginning of our game loop so that we can track the
  * elapsed difference. */
  _engineTimer.Start();

}

void GameEngine::Shutdown()
{
	/* Stop the engine timer as we're shutting down. */
	_engineTimer.Stop();

	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	
	//delete map;
	//delete playerOne;
	//delete playerTwo;

	for (int i = 0; i < 10; ++i)
	{
		if (_playerOneAmmo[i] != NULL)
		{
			delete _playerOneAmmo[i];
		}

		if (_playerTwoAmmo[i] != NULL)
		{
			delete _playerTwoAmmo[i];
		}
	}

	/* Quit and clean up all libraries. */
	IMG_Quit();
	SDL_Quit();
}

void GameEngine::Update()
{
	char title[50] = "TANKS ~ Player one: ";
	char playerOneScore[20];
	char playerTwoScore[20];

	_itoa_s(playerOne->getScore(), playerOneScore, 20);
	_itoa_s(playerTwo->getScore(), playerTwoScore, 20);

	strcat_s(title, playerOneScore);
	strcat_s(title, "          Player two: ");
	strcat_s(title, playerTwoScore);
	SDL_SetWindowTitle(_window, title);


	SDL_Event evt;
	SDL_PollEvent(&evt);
	// Calculating the time difference since our last loop.
	_engineTimer.Update();

	// Check if players are alive
	if (!(playerOne->isAlive()) || !(playerTwo->isAlive()))
	{
		_deathTime = (_deathTime - _engineTimer.GetDeltaTime());

		if (_deathTime <= 0)
		{
			playerOne->Spawn();
			playerTwo->Spawn();
		}
	}

	// Handle keyboard input
	if (evt.type == SDL_KEYDOWN)
	{
		SDL_KeyboardEvent &keyEvt = evt.key;
		SDL_Keycode &keyCode = keyEvt.keysym.sym;

		switch (keyCode)
		{
			// Player one movement using arrow keys
			case SDLK_UP:
				if (playerOne->isAlive())
				{
					playerOne->SetSpeed(playerOne->GetSpeed() + 5);
					if (playerOne->GetSpeed() > 150)
						playerOne->SetSpeed(150);
				}
				break;
			case SDLK_DOWN:
				if (playerOne->isAlive())
				{
					playerOne->SetSpeed((playerOne->GetSpeed()) - 5);
					if (playerOne->GetSpeed() < 0)
						playerOne->SetSpeed(0);
				}
				break;
			case SDLK_LEFT:
				if (playerOne->isAlive())
				{
					if (playerOne->GetRotation() <= 0)
						playerOne->SetRotation(350);
					else
						playerOne->SetRotation(playerOne->GetRotation() - 10);
				}
				break;
			case SDLK_RIGHT:
				if (playerOne->isAlive())
				{
					if (playerOne->GetRotation() >= 350)
						playerOne->SetRotation(0);
					else
						playerOne->SetRotation(playerOne->GetRotation() + 10);
				}
				break;

				// Player two movement using WASD
			case SDLK_w:
				if (playerTwo->isAlive())
				{
					playerTwo->SetSpeed(playerTwo->GetSpeed() + 5);
					if (playerTwo->GetSpeed() > 150)
						playerTwo->SetSpeed(150);
				}
				break;
			case SDLK_s:
				if (playerTwo->isAlive())
				{
					playerTwo->SetSpeed(playerTwo->GetSpeed() - 5);
					if (playerTwo->GetSpeed() < 0)
						playerTwo->SetSpeed(0);
				}
				break;
			case SDLK_a:
				if (playerTwo->isAlive())
				{
					if (playerTwo->GetRotation() <= 0)
						playerTwo->SetRotation(350);
					else
						playerTwo->SetRotation(playerTwo->GetRotation() - 10);
				}
				break;
			case SDLK_d:
				if (playerTwo->isAlive())
				{
					if (playerTwo->GetRotation() >= 350)
						playerTwo->SetRotation(0);
					else
						playerTwo->SetRotation(playerTwo->GetRotation() + 10);
				}
				break;

				// Player one fire control
			case SDLK_RSHIFT:
				if (playerOne->isAlive() && playerTwo->isAlive())
				{
					for (int i = 0; i < 10; i++)
					{
						if (_playerOneAmmo[i] == NULL)
						{
							_playerOneAmmo[i] = new Bullet();
							_playerOneAmmo[i]->Initialize(_renderer, "");
							_playerOneAmmo[i]->Shot(playerOne->GetPosition(), playerOne->GetRotation() - 180);
							break;
						}
						else if (_playerOneAmmo[i]->GetLife() <= 0)
						{
							_playerOneAmmo[i]->Initialize(_renderer, "");
							_playerOneAmmo[i]->Shot(playerOne->GetPosition(), playerOne->GetRotation() - 180);
						}
					}
				}
				break;
				// Player two fire control
			case SDLK_LSHIFT:
				if (playerTwo->isAlive() && playerOne->isAlive())
				{
					for (int i = 0; i < 10; i++)
					{
						if (_playerTwoAmmo[i] == NULL)
						{
							_playerTwoAmmo[i] = new Bullet();
							_playerTwoAmmo[i]->Initialize(_renderer, "");
							_playerTwoAmmo[i]->Shot(playerTwo->GetPosition(), playerTwo->GetRotation() - 180);
							break;
						}
						else if (_playerTwoAmmo[i]->GetLife() <= 0)
						{
							_playerTwoAmmo[i]->Initialize(_renderer, "");
							_playerTwoAmmo[i]->Shot(playerTwo->GetPosition(), playerTwo->GetRotation() - 180);
						}
					}
				}
				break;
		}
	}

	// Update bullets
	for (int i = 0; i < 10; ++i)
	{
		if (_playerOneAmmo[i] != NULL)
		{
			if (_playerOneAmmo[i]->GetLife() > 0)
				_playerOneAmmo[i]->Update(_engineTimer.GetDeltaTime());
		}
	}

	for (int j = 0; j < 10; ++j)
	{
		if (_playerTwoAmmo[j] != NULL)
		{
			if (_playerTwoAmmo[j]->GetLife() > 0)
				_playerTwoAmmo[j]->Update(_engineTimer.GetDeltaTime());
		}
	}

	// Player 1 shots
	for (int i = 0; i < 10; ++i)
	{
		if (_playerOneAmmo[i] != NULL)
		{
			// Wall
			if (map->checkCollision(_playerOneAmmo[i]->GetLocation()) ||
				_playerOneAmmo[i]->GetLocation().x <= 0 || _playerOneAmmo[i]->GetLocation().y <= 0 ||
				_playerOneAmmo[i]->GetLocation().x >= 640 || _playerOneAmmo[i]->GetLocation().y >= 640)
			{
				_playerOneAmmo[i]->Bounce();

				// Make sure bullet isn't out of bounds
				if (map->checkCollision(_playerOneAmmo[i]->lookAhead(_engineTimer.GetDeltaTime())) ||
					_playerOneAmmo[i]->lookAhead(_engineTimer.GetDeltaTime()).x <= 0 || _playerOneAmmo[i]->lookAhead(_engineTimer.GetDeltaTime()).y <= 0 ||
					_playerOneAmmo[i]->lookAhead(_engineTimer.GetDeltaTime()).x >= 640 || _playerOneAmmo[i]->lookAhead(_engineTimer.GetDeltaTime()).y >= 640)
				{
					_playerOneAmmo[i]->SetDirection(_playerOneAmmo[i]->GetDirection());
				}
			}

			// Check for player collision
			if (playerTwo->CheckCollision(_playerOneAmmo[i]->GetLocation()))
			{
				playerTwo->Kill();
				_deathTime = 2;
				_playerOneAmmo[i]->Destroy();
				playerOne->incrementScore();
			}
		}
	}

	// Player 2 shots
	for (int j = 0; j < 10; ++j)
	{
		if (_playerTwoAmmo[j] != NULL)
		{
			// Wall
			if (map->checkCollision(_playerTwoAmmo[j]->GetLocation()) ||
				_playerTwoAmmo[j]->GetLocation().x <= 0 || _playerTwoAmmo[j]->GetLocation().y <= 0 ||
				_playerTwoAmmo[j]->GetLocation().x >= 640 || _playerTwoAmmo[j]->GetLocation().y >= 640)
			{
				_playerTwoAmmo[j]->Bounce();

				// Make sure bullet isn't out of bounds
				if (map->checkCollision(_playerTwoAmmo[j]->lookAhead(_engineTimer.GetDeltaTime())) ||
					_playerTwoAmmo[j]->lookAhead(_engineTimer.GetDeltaTime()).x <= 0 || _playerTwoAmmo[j]->lookAhead(_engineTimer.GetDeltaTime()).y <= 0 ||
					_playerTwoAmmo[j]->lookAhead(_engineTimer.GetDeltaTime()).x >= 640 || _playerTwoAmmo[j]->lookAhead(_engineTimer.GetDeltaTime()).y >= 640)
				{
					_playerTwoAmmo[j]->SetDirection(_playerTwoAmmo[j]->GetDirection());
				}
			}

			// Check for player collision
			if (playerOne->CheckCollision(_playerTwoAmmo[j]->GetLocation()))
			{
				playerOne->Kill();
				_deathTime = 2;
				_playerTwoAmmo[j]->Destroy();
				playerTwo->incrementScore();
			}
		}
	}

	// Check player collision
	if (playerTwo->CheckCollision(playerOne->GetPosition()))
	{
		playerOne->NudgePlayer(_engineTimer.GetDeltaTime());
		playerTwo->NudgePlayer(_engineTimer.GetDeltaTime());
	}

	// Check if player one collides with a wall
	if (map->checkCollision(playerOne->GetPosition()))
	{
		playerOne->NudgePlayer(_engineTimer.GetDeltaTime());
	}

	// check if player two collides with a wall
	if (map->checkCollision(playerTwo->GetPosition()))
	{
		playerTwo->NudgePlayer(_engineTimer.GetDeltaTime());
	}

	if (playerOne->isAlive())
		playerOne->Update(_engineTimer.GetDeltaTime());
	if (playerTwo->isAlive())
		playerTwo->Update(_engineTimer.GetDeltaTime());

	UpdateImpl(_engineTimer.GetDeltaTime());
}

void GameEngine::Draw()
{
  // Set the draw colour for screen clearing.
  SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

  // Clear the renderer with the current draw colour.
  SDL_RenderClear(_renderer);

  map->Draw(_renderer, _engineTimer.GetDeltaTime());

  if (playerOne->isAlive())
	playerOne->Draw(_renderer, _engineTimer.GetDeltaTime());
  if (playerTwo->isAlive())
	playerTwo->Draw(_renderer, _engineTimer.GetDeltaTime());

  // Draw the bullets
  for (int i = 0; i < 10; ++i)
  {
	  if (_playerOneAmmo[i] != NULL)
	  {
		  if (_playerOneAmmo[i]->GetLife() > 0)
			  _playerOneAmmo[i]->Draw(_renderer, _engineTimer.GetDeltaTime());
	  }
  }

  for (int j = 0; j < 10; ++j)
  {
	  if (_playerTwoAmmo[j] != NULL)
	  {
		  if (_playerTwoAmmo[j]->GetLife() > 0)
			  _playerTwoAmmo[j]->Draw(_renderer, _engineTimer.GetDeltaTime());
	  }
  }

  // Present what is in our renderer to our window.
  SDL_RenderPresent(_renderer);
}