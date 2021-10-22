#pragma once
#pragma once
#include "SDL.h"
#include <iostream>
using namespace std;

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void UpdateInputs();
	void ChangeKeyState(SDL_Event event, bool state);

	bool wDown = false;
	bool sDown = false;
	bool dDown = false;
	bool aDown = false;
	bool kDown = false;			// Button you shoot with
	bool rDown = false;

	bool quitPressed = false;
};

