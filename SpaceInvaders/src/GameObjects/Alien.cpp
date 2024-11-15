#include "Alien.h"

#include "Core/Spritesheet.h"

#include <cstdlib>

void Alien::Start() noexcept
{
	SpritesheetLoader& loader = SpritesheetLoader::GetInstance();
	
	m_Sprite.SpritesheetRef = &loader.GetSpritesheet("SpaceInvaders");
	m_Sprite.X = rand() % 5;
	m_Sprite.Y = rand() % 2;

	m_Transform.Position = { (float)(rand() % 900), 0};
	m_Transform.Scale = { 5, 5 };

	Vector2 down{ 0, 1 };
	Vector2 right{ 1, 0 };
	Vector2 left{ -1, 0 };

	{
		float length = std::sqrtf(m_RightDown.x * m_RightDown.x + m_RightDown.y * m_RightDown.y);
		m_RightDown.x /= length;
		m_RightDown.y /= length;
	}

	{
		float length = std::sqrtf(m_LeftDown.x * m_LeftDown.x + m_LeftDown.y * m_LeftDown.y);
		m_LeftDown.x /= length;
		m_LeftDown.y /= length;
	}

	int toLeft = rand() % 2;

	if (toLeft)
		m_Direction = m_LeftDown;
	else
		m_Direction = m_RightDown;
}

void Alien::Update(float dt) noexcept
{
	m_Transform.Position.x += m_Direction.x * m_Speed * dt;
	m_Transform.Position.y += m_Direction.y * m_Speed * dt;

	if (m_Transform.Position.x > (950 - 80))
		m_Direction = m_LeftDown;
	else if (m_Transform.Position.x < 10)
		m_Direction = m_RightDown;
}
