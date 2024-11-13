#pragma once

#include "raylib.h"

#include <cstdint>

struct Transform2D
{
	Vector2 Position;
	Vector2 Scale;
};

struct Sprite
{
	uint32_t X;
	uint32_t Y;

	class Spritesheet* SpritesheetRef;
};