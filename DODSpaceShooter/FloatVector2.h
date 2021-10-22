#pragma once
#include <math.h>


struct FVector2
{
	float X, Y;

	FVector2(float x, float y)
	{
		X = x;
		Y = y;
	}
	FVector2()
	{
		X = 0;
		Y = 0;
	}

	friend FVector2 operator +(FVector2 a, const FVector2& b)
	{
		return FVector2(a.X + b.X, a.Y + b.Y);
	}

	friend FVector2 operator -(FVector2 a, const FVector2& b)
	{
		return FVector2(a.X - b.X, a.Y - b.Y);
	}

	friend FVector2 operator *(FVector2 a, const float& b)
	{
		return FVector2(a.X * b, a.Y * b);
	}

	FVector2& operator +=(const FVector2& a) 
	{
		X + a.X;
		Y + a.Y;
		return *this;
	}

	static double Distance(FVector2 distanceFrom, FVector2 distanceTo)
	{
		return Distance(distanceFrom.X, distanceFrom.Y, distanceTo.X, distanceTo.Y);
	}

	static double Distance(double distanceFromX, double distanceFromY, double distanceToX, double distanceToY)
	{
		double power = pow(distanceFromX - distanceToX, 2) + pow(distanceFromY - distanceToY, 2) * 1.0;

		return sqrt(power);
	}

	double Magnitude() { return sqrt(X * X + Y * Y); }

	FVector2 Normalized()
	{
		double magn = Magnitude();
		return FVector2(X / magn, Y / magn);
	}
};