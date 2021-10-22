#pragma once
#include "FloatVector2.h"
#include "FColor.h"
#include "SDL.h"
#include <vector>
using namespace std;
using std::vector;


class AstroidSystem
{
	int NumberOfAstroids = 0;
	struct Astroids
	{
		vector<FVector2> Positions;
		vector<FVector2> Positions2;
		vector<FVector2> Positions3;
		vector<FVector2> Positions4;

		vector<FVector2> Velocities;
		vector<FVector2> Velocities2;
		vector<FVector2> Velocities3;
		vector<FVector2> Velocities4;

		vector<FColor> Colors;
		vector<float> Radii;
	};


	Astroids AstroidArrays;
	float AvoidDistance = 100;

public:
	AstroidSystem(int NumberOfAstroids);

	void AstroidPositionUpdate(float DeltaTime, vector<FVector2>& Positions, vector<FVector2> Velocities);
	void AstroidWallCollision(vector<FVector2> Positions, vector<FVector2>& Velocities);
	void AstroidPlayeravoidance(FVector2 PlayerPosition, float DeltaTime, vector<FVector2> Positions, vector<FVector2>& Velocities);
	void AstroidUpdate(float DeltaTime, FVector2 PlayerPosition);
	void AstroidRender(SDL_Renderer* renderer);
};