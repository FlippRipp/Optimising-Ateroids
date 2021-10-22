#pragma once
using namespace std;
#include "SDL.h"
#include <iostream>
#include <SDL_image.h>
#include <string>

class AstroidSystem;
class InputSystem;
class Player;

class Game
{
public:
	Game(const char* title, int resX, int resY, bool fullscreen);
	~Game();

	void GameLoop();
	void Update();
	void Render();
	double GetTimeSec() { return gameTime / 1000; }


	const double DesiredFps = 60;
	const double msPerSecond = 1000;
	double gameTime;
	double deltaTime;
	int frameCounter;
private:
	void Reset();

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	SDL_Color color = { 0,255,0 };
	SDL_Rect textRect;
	SDL_Texture* texture;

	int cycleCount;
	double accumilator = 0;
	double cycleTime;
	double independedGameTime;

	AstroidSystem* Astroids;
	InputSystem* Input;
	Player* PlayerCharacter;

	bool isRunning = true;
};

