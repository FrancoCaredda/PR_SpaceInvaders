#pragma once

#include "Core/Components.h"
#include "raylib.h"

struct Projectile
{
	Color ProjectileColor{ 148, 208, 62, 255};
	Transform2D ProjectileTranform{};

	float Radius = 5;
	float Velocity = 1000.0f;
	float Lifetime = 1.5;

	bool Active = false;

	inline Rectangle GetBoundingBox() const noexcept 
	{
		return Rectangle{ ProjectileTranform.Position.x,
			ProjectileTranform.Position.y,
			Radius, Radius };
	}
};