#pragma once
#include "FloatVector2.h"
#include "SDL.h"

class InputSystem;
class Player
{
public:
	FVector2 Position;

	Player();

	float MovementSpeed = 10;

	void PlayerUpdate(float DeltaTime, InputSystem* Input);
	void PlayerMove(float DeltaTime, InputSystem* Input);
	void RenderPlayer(SDL_Renderer* renderer);


};

