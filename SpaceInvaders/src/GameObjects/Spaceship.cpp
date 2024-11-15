#include "Spaceship.h"
#include "GameObjectPool.h"

#include "Core/Spritesheet.h"

#include <iostream>

void Spaceship::Start() noexcept
{
	SpritesheetLoader& loader = SpritesheetLoader::GetInstance();

	m_Sprite.X = 0;
	m_Sprite.Y = 1;
	m_Sprite.SpritesheetRef = &loader.GetSpritesheet("SpaceInvaders_Ships");

	m_Transform.Position = Vector2{950.0f / 2.0f, 400.0f };
	m_Transform.Scale = Vector2{ 5, 5 };

	const Rectangle& boundingBox = GetBoundingBox();

	m_Transform.Position.y -= boundingBox.height;

	m_MousePosition = m_Transform.Position;
	SetMousePosition(950.0f / 2.0f, 400.0f / 2.0f);
	m_PreviousMousePosition = GetMousePosition();
}

void Spaceship::Update(float dt) noexcept
{
	GameObjectPool& pool = GameObjectPool::GetInstance();
	Rectangle boundingBox = GetBoundingBox();

	if (m_ShootingDelay > 0)
		m_ShootingDelay -= dt;

	Vector2 deltaMousePosition = GetMousePosition();
	deltaMousePosition.x -= m_PreviousMousePosition.x;
	deltaMousePosition.y -= m_PreviousMousePosition.y;

	SetMousePosition(950.0f / 2.0f, 400.0f / 2.0f);

	if (m_Transform.Position.x > (950 - 80))
		m_Transform.Position.x = (950 - 80);
	else if (m_Transform.Position.x < 10)
		m_Transform.Position.x = 10;

	m_Transform.Position.x += m_Speed * deltaMousePosition.x * dt;


	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && m_ShootingDelay < 0)
	{
		Vector2 position{
			m_Transform.Position.x + boundingBox.width / 2.0f, 
			m_Transform.Position.y + boundingBox.height / 4.0f 
		};

		Projectile* projectile = pool.SpawnProjectile(position);

		if (projectile)
			projectile->Lifetime = 1.5f;

		m_ShootingDelay = ShootingDelay;
	}
}

void Spaceship::OnTriggerOverlapped(Object* other) noexcept
{
}
