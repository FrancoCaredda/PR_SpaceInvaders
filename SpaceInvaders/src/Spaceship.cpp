#include "Spaceship.h"

#include "Core/Spritesheet.h"

void Spaceship::Start() noexcept
{
	SpritesheetLoader& loader = SpritesheetLoader::GetInstance();

	m_Sprite.X = 0;
	m_Sprite.Y = 1;
	m_Sprite.SpritesheetRef = &loader.GetSpritesheet("SpaceInvaders_Ships");

	m_Transform.Position = Vector2{ 50, 50 };
	m_Transform.Scale = Vector2{ 5, 5 };
}

void Spaceship::Update(float dt) noexcept
{

}
