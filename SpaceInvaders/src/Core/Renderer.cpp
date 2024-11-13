#include "Renderer.h"
#include "Components.h"
#include "Spritesheet.h"

#include <stdexcept>

Renderer* Renderer::s_Instance = nullptr;

Renderer::Renderer()
{
	if (s_Instance)
		throw std::runtime_error::exception("There cannot be two instances of the Renderer class");

	s_Instance = this;
}

void Renderer::SetFramebufferSize(const Vector2& size)
{
	m_FramebufferSize = size;
}

void Renderer::DrawObjects(const std::vector<Object*>& objects)
{
	for (Object* object : objects)
	{
		Transform2D transform = object->GetTransform();
		Sprite sprite = object->GetSprite();

		Spritesheet* spritesheet = sprite.SpritesheetRef;

		Vector2 cellDimension = spritesheet->GetCellSize();

		Rectangle source{
			sprite.Y * cellDimension.x,
			sprite.X * cellDimension.y,
			cellDimension.x, cellDimension.y
		};

		DrawTexturePro(spritesheet->GetNative(),
			source,
			object->GetBoundingBox(),
			{ -transform.Position.x, -transform.Position.y },
			0,
			RAYWHITE);

	}
}

Renderer& Renderer::GetInstance() noexcept
{
	return *s_Instance;
}
