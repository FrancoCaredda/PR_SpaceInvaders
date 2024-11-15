#include "Physics.h"

#include "raylib.h"

namespace Physics {

	static bool AIsToTheRightOfB(const Rectangle& rect1, const Rectangle& rect2)
	{
		Vector2 A1{ rect1.x, rect1.y };
		Vector2 A2{ rect1.x, rect1.y + rect1.height };

		Vector2 B3{ rect2.x + rect2.width, rect2.y };
		Vector2 B4{ rect2.x + rect2.width, rect2.y + rect2.height };

		return A1.x > B3.x && 
			   A2.x > B4.x;
	}
	static bool AIsToTheLeftOfB(const Rectangle& rect1, const Rectangle& rect2)
	{
		Vector2 A3{ rect1.x + rect1.width, rect1.y };
		Vector2 A4{ rect1.x + rect1.width, rect1.y + rect1.height };

		Vector2 B1{ rect2.x, rect2.y };
		Vector2 B2{ rect2.x, rect2.y + rect2.height };

		return A3.x < B1.x &&
			   A4.x < B2.x;
	}
	static bool AIsAboveB(const Rectangle& rect1, const Rectangle& rect2)
	{
		Vector2 A2{ rect1.x, rect1.y + rect1.height };
		Vector2 A4{ rect1.x + rect1.width, rect1.y + rect1.height };

		Vector2 B1{ rect2.x, rect2.y };
		Vector2 B3{ rect2.x + rect2.width, rect2.y };

		return A2.y < B1.y &&
			   A4.y < B3.y;
	}
	static bool AIsBelowB(const Rectangle& rect1, const Rectangle& rect2)
	{
		Vector2 A1{ rect1.x, rect1.y };
		Vector2 A3{ rect1.x + rect1.width, rect1.y };

		Vector2 B2{ rect2.x, rect2.y + rect2.height };
		Vector2 B4{ rect2.x + rect2.width, rect2.y + rect2.height };

		return A1.y > B2.y &&
			   A3.y > B4.y;
	}

	bool AreRectanglesColliding(const Rectangle& rect1, const Rectangle& rect2)
	{
		return !(
			AIsToTheRightOfB(rect1, rect2) ||
			AIsToTheLeftOfB(rect1, rect2)  ||
			AIsAboveB(rect1, rect2) ||
			AIsBelowB(rect1, rect2)
		);
	}
}