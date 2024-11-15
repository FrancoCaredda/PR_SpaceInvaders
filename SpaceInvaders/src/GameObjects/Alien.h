#pragma once

#include "Core/Object.h"

class Alien : public Object
{
public:
	Alien() = default;
	~Alien() = default;

	void Start() noexcept override;
	void Update(float dt) noexcept override;
private:
	Vector2 m_Direction;
	Vector2 m_RightDown{ 1, 1 };
	Vector2 m_LeftDown{ -1, 1 };

	float m_Speed = 100.0;
};