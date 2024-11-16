#include "Object.h"
#include "Spritesheet.h"

#include <cmath>

const Rectangle& Object::GetBoundingBox() const noexcept
{
	Vector2 cellDimension = m_Sprite.SpritesheetRef->GetCellSize();

	return Rectangle{
		m_Transform.Position.x, m_Transform.Position.y,
		cellDimension.x * m_Transform.Scale.x, cellDimension.y * m_Transform.Scale.y
	};
}
