#include "Object.h"
#include "Spritesheet.h"

#include <cmath>

const Rectangle& Object::GetBoundingBox() const noexcept
{
	if (std::abs(m_BoundingBox.width) < 1e-4)
	{
		Vector2 cellDimension = m_Sprite.SpritesheetRef->GetCellSize();

		m_BoundingBox = Rectangle{
			m_Transform.Position.x, m_Transform.Position.y,
			cellDimension.x * m_Transform.Scale.x, cellDimension.y * m_Transform.Scale.y
		};
	}
	
	return m_BoundingBox;
}
