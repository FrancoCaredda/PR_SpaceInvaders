#pragma once

struct Rectangle;

namespace Physics {
	bool AreRectanglesColliding(const Rectangle& rect1, const Rectangle& rect2);
}