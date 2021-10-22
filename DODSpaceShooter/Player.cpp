#include "Player.h"
#include "InputSystem.h"
#include "Primitives.h"
#include <iostream>

Player::Player()
{
	Position = FVector2(500, 500);
}

void Player::PlayerUpdate(float DeltaTime, InputSystem* Input)
{
	PlayerMove(DeltaTime, Input);
}

void Player::PlayerMove(float DeltaTime, InputSystem* Input)
{
	FVector2 DeltaMove;

	if (Input->wDown)
	{
		DeltaMove.Y -= MovementSpeed;

	}
	if (Input->sDown)
	{
		DeltaMove.Y += MovementSpeed;

	}
	if (Input->aDown)
	{
		DeltaMove.X -= MovementSpeed;

	}
	if (Input->dDown)
	{
		DeltaMove.X += MovementSpeed;
	}

	Position = Position + DeltaMove;

}

void Player::RenderPlayer(SDL_Renderer* renderer)
{
	filledCircleRGBA(renderer, Position.X, Position.Y, 50, 255, 0, 100, 255);
}
