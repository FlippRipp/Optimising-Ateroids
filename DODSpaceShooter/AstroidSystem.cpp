#include "AstroidSystem.h"
#include "Primitives.h"
#include <iostream>
#include  <thread>


AstroidSystem::AstroidSystem(int n)
{
	NumberOfAstroids = n;
	AstroidArrays.Positions.reserve(NumberOfAstroids );
	AstroidArrays.Velocities.reserve(NumberOfAstroids );

	AstroidArrays.Positions2.reserve(NumberOfAstroids );
	AstroidArrays.Velocities2.reserve(NumberOfAstroids );

	AstroidArrays.Positions3.reserve(NumberOfAstroids );
	AstroidArrays.Velocities3.reserve(NumberOfAstroids );

	AstroidArrays.Colors.reserve(NumberOfAstroids);
	AstroidArrays.Radii.reserve(NumberOfAstroids);

	for (int i = 0; i < NumberOfAstroids; i++)
	{
		int PosX = rand() % 500 + 250;
		int PosY = rand() % 500 + 250;

		int XSign = ((double)(rand() % 2) - 0.5) * 2;
		int YSign = ((double)(rand() % 2) - 0.5) * 2;

		int VelX = rand() % 10 * XSign + XSign;
		int VelY = rand() % 10 * YSign + YSign;

		int ColorR = rand() * 255;
		int ColorG = rand() * 255;
		int ColorB = rand() * 255;

		if (NumberOfAstroids > NumberOfAstroids / 4 * 3)
		{
			AstroidArrays.Positions4.push_back(FVector2(PosX, PosY));
			AstroidArrays.Velocities4.push_back(FVector2(VelX, VelY));

		}
		else if (NumberOfAstroids > NumberOfAstroids / 4 * 2)
		{
			AstroidArrays.Positions3.push_back(FVector2(PosX, PosY));
			AstroidArrays.Velocities3.push_back(FVector2(VelX, VelY));
		}
		else if (NumberOfAstroids > NumberOfAstroids / 4)
		{
			AstroidArrays.Positions2.push_back(FVector2(PosX, PosY));
			AstroidArrays.Velocities2.push_back(FVector2(VelX, VelY));
		}
		else
		{
			AstroidArrays.Positions.push_back(FVector2(PosX, PosY));
			AstroidArrays.Velocities.push_back(FVector2(VelX, VelY));
		}

		AstroidArrays.Colors.push_back(FColor(ColorR, ColorG, ColorB, 255));
		AstroidArrays.Radii.push_back(10);
	}
}

void AstroidSystem::AstroidUpdate(float DeltaTime, FVector2 PlayerPosition)
{
	std::thread UPt1(&AstroidSystem::AstroidPositionUpdate, this, DeltaTime, std::ref(AstroidArrays.Positions), AstroidArrays.Velocities);
	std::thread UPt2(&AstroidSystem::AstroidPositionUpdate, this, DeltaTime, std::ref(AstroidArrays.Positions2), AstroidArrays.Velocities2);
	std::thread UPt3(&AstroidSystem::AstroidPositionUpdate, this, DeltaTime, std::ref(AstroidArrays.Positions3), AstroidArrays.Velocities3);
	std::thread UPt4(&AstroidSystem::AstroidPositionUpdate, this, DeltaTime, std::ref(AstroidArrays.Positions4), AstroidArrays.Velocities4);

	UPt1.join();
	UPt2.join();
	UPt3.join();
	UPt4.join();

	std::thread WCt1(&AstroidSystem::AstroidWallCollision, this, AstroidArrays.Positions, std::ref(AstroidArrays.Velocities));
	std::thread WCt2(&AstroidSystem::AstroidWallCollision, this, AstroidArrays.Positions2, std::ref(AstroidArrays.Velocities2));
	std::thread WCt3(&AstroidSystem::AstroidWallCollision, this, AstroidArrays.Positions3, std::ref(AstroidArrays.Velocities3));
	std::thread WCt4(&AstroidSystem::AstroidWallCollision, this, AstroidArrays.Positions4, std::ref(AstroidArrays.Velocities4));

	WCt1.join();
	WCt2.join();
	WCt3.join();
	WCt4.join();

	std::thread PAt1(&AstroidSystem::AstroidPlayeravoidance, this, PlayerPosition, DeltaTime, AstroidArrays.Positions, std::ref(AstroidArrays.Velocities));
	std::thread PAt2(&AstroidSystem::AstroidPlayeravoidance, this, PlayerPosition,  DeltaTime, AstroidArrays.Positions2, std::ref(AstroidArrays.Velocities2));
	std::thread PAt3(&AstroidSystem::AstroidPlayeravoidance, this, PlayerPosition, DeltaTime, AstroidArrays.Positions3, std::ref(AstroidArrays.Velocities3));
	std::thread PAt4(&AstroidSystem::AstroidPlayeravoidance, this, PlayerPosition, DeltaTime, AstroidArrays.Positions4, std::ref(AstroidArrays.Velocities4));

	PAt1.join();
	PAt2.join();
	PAt3.join();
	PAt4.join();

}

void AstroidSystem::AstroidPositionUpdate(float DeltaTime, vector<FVector2>& Positions, vector<FVector2> Velocities)
{
	for (int i = 0; i < Positions.size(); i++)
	{

		Positions[i] = Positions[i] + Velocities[i];

	}
}

void AstroidSystem::AstroidWallCollision(vector<FVector2> Positions, vector<FVector2>& Velocities)
{
	for (int i = 0; i < Positions.size(); i++)
	{
		bool OtsideOfBounds = false;
		if (Positions[i].X < 0) OtsideOfBounds = true;
		if (Positions[i].X > 1000) OtsideOfBounds = true;
		if (Positions[i].Y < 0) OtsideOfBounds = true;
		if (Positions[i].Y > 1000) OtsideOfBounds = true;

		if (OtsideOfBounds)
		{
			Velocities[i] = FVector2(-Velocities[i].X, -Velocities[i].Y);
		}
	}
}

void AstroidSystem::AstroidPlayeravoidance(FVector2 PlayerPosition, float DeltaTime, vector<FVector2> Positions, vector<FVector2>& Velocities)
{
	for (int i = 0; i < Positions.size(); i++)
	{
		float Distance = FVector2::Distance(Positions[i], PlayerPosition);

		if (Distance < AvoidDistance - 10)
		{
			Velocities[i] = (Positions[i] - PlayerPosition).Normalized() * Velocities[i].Magnitude();
		}
	}
}


void AstroidSystem::AstroidRender(SDL_Renderer* renderer)
{
	int ColorIterator = 0;
	for (int i = 0; i < AstroidArrays.Positions.size(); i++)
	{
		FVector2 Pos = AstroidArrays.Positions[i];
		FColor Col = AstroidArrays.Colors[ColorIterator];
		pixelRGBA(renderer, Pos.X, Pos.Y, Col.R, Col.G, Col.B, 255);
		ColorIterator++;
		//int error = circleRGBA(renderer, Pos.X, Pos.Y, 1, Col.R, Col.G, Col.B, 255);
	}

	for (int i = 0; i < AstroidArrays.Positions2.size(); i++)
	{
		FVector2 Pos = AstroidArrays.Positions2[i];
		FColor Col = AstroidArrays.Colors[ColorIterator];
		pixelRGBA(renderer, Pos.X, Pos.Y, Col.R, Col.G, Col.B, 255);
		ColorIterator++;
		//int error = circleRGBA(renderer, Pos.X, Pos.Y, 1, Col.R, Col.G, Col.B, 255);
	}

	for (int i = 0; i < AstroidArrays.Positions3.size(); i++)
	{
		FVector2 Pos = AstroidArrays.Positions3[i];
		FColor Col = AstroidArrays.Colors[ColorIterator];
		pixelRGBA(renderer, Pos.X, Pos.Y, Col.R, Col.G, Col.B, 255);
		ColorIterator++;
		//int error = circleRGBA(renderer, Pos.X, Pos.Y, 1, Col.R, Col.G, Col.B, 255);
	}
	for (int i = 0; i < AstroidArrays.Positions4.size(); i++)
	{
		FVector2 Pos = AstroidArrays.Positions4[i];
		FColor Col = AstroidArrays.Colors[ColorIterator];
		pixelRGBA(renderer, Pos.X, Pos.Y, Col.R, Col.G, Col.B, 255);
		ColorIterator++;
		//int error = circleRGBA(renderer, Pos.X, Pos.Y, 1, Col.R, Col.G, Col.B, 255);
	}
}
