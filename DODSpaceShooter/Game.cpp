#include "Game.h"
#include "Primitives.h"
#include "AstroidSystem.h"
#include "InputSystem.h"
#include "Player.h"

Game::Game(const char* title, int resX, int resY, bool fullscreen)
{
	Astroids = new AstroidSystem(100000);
	Input = new InputSystem();
	PlayerCharacter = new Player();
	int error = SDL_Init(SDL_INIT_EVERYTHING);
	if (error == 0)
	{
		int flag = 0;
		if (fullscreen)
		{
			flag = SDL_WINDOW_FULLSCREEN;
		}
		cout << "Init Success" << endl;
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resX, resY, flag);

		if (window)
		{
			cout << "Window successfully created" << endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			cout << "Renderer successfully created" << endl;
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			int imageFlags = IMG_INIT_PNG;
			/*if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "IMG_Init failed to created SDL_image Error: %s/n" << IMG_GetError() << endl;
			}
			else
			{
				cout << "IMG_Init successfully created" << endl;
			}*/
		}

		SDL_RenderPresent(renderer);
	}
	else
	{
		cout << "Error on SDL Init Error code: " << error << endl;
	}
}

Game::~Game()
{
}

void Game::Update()
{
	Input->UpdateInputs();
	PlayerCharacter->PlayerUpdate(deltaTime, Input);
	Astroids->AstroidUpdate(deltaTime, PlayerCharacter->Position);
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	//render stuff here	
	PlayerCharacter->RenderPlayer(renderer);
	//Astroids->AstroidRender(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderPresent(renderer);
}

void Game::Reset()
{
	gameTime = 0;
}

void Game::GameLoop() {

	while (isRunning)
	{
		cycleCount++;
		if (cycleCount % 3 == 0)
		{
			double newTime = SDL_GetTicks();
			cycleTime = (newTime - independedGameTime) / 3;
			independedGameTime = newTime;
		}

		accumilator += cycleTime;

		double framesec = 1 / DesiredFps;
		double frameMiliSec = framesec * msPerSecond;
		//cout << "accumilator = " << accumilator << endl;
		//cout << "frameMiliSec = " << frameMiliSec << endl;
		if (accumilator > frameMiliSec)
		{
			frameCounter++;
			accumilator = 0;
			double newTime = SDL_GetTicks();
			deltaTime = (newTime - gameTime) / 1000;
			gameTime = newTime;
			cout << "deltatime = " << deltaTime * 60 << " gametime = " << gameTime << endl;
			//cout << frameCounter / (gameTime / 1000) << endl;
			Update();
			Render();
		}
	}


	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}