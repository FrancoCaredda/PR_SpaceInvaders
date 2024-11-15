#include "Renderer.h"
#include "Components.h"
#include "Spritesheet.h"
#include "Object.h"

#include "GameObjects/Projectile.h"

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

		Rectangle boundingBox = object->GetBoundingBox();
		boundingBox.x = 0;
		boundingBox.y = 0;

		DrawTexturePro(spritesheet->GetNative(),
			source,
			boundingBox,
			{ -transform.Position.x , -transform.Position.y },
			0,
			RAYWHITE);

	}
}

void Renderer::DrawBoundingBoxes(const std::vector<class Object*>& objects)
{
	for (Object* object : objects)
	{
		Transform2D transform = object->GetTransform();

		Rectangle boundingBox = object->GetBoundingBox();

		DrawRectangleLines(boundingBox.x,
			boundingBox.y,
			boundingBox.width,
			boundingBox.height,
			Color{0, 255, 0, 255});
	}
}

void Renderer::DrawProjectiles(const std::vector<Projectile>& projectiles)
{
	for (const Projectile& projectile : projectiles)
	{
		if (projectile.Active)
		{
			DrawCircle(projectile.ProjectileTranform.Position.x,
				projectile.ProjectileTranform.Position.y,
				projectile.Radius,
				projectile.ProjectileColor);
		}
	}
}

Renderer& Renderer::GetInstance() noexcept
{
	return *s_Instance;
}
