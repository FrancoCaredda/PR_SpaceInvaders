#pragma once

#include "Core/Object.h"

class Spaceship : public Object
{
public:
	Spaceship() = default;
	~Spaceship() = default;

	virtual void Start() noexcept override;
	virtual void Update(float dt) noexcept override;
	virtual void OnTriggerOverlapped(Object* other) noexcept override;
private:
	const float ShootingDelay = 0.25f;

	float m_ShootingDelay = ShootingDelay;
	float m_Speed = 50.0f;

	Vector2 m_PreviousMousePosition;
	Vector2 m_MousePosition;
};