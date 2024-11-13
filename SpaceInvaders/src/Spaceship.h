#pragma once

#include "Core/Object.h"

class Spaceship : public Object
{
public:
	Spaceship() = default;
	~Spaceship() = default;

	void Start() noexcept override;
	void Update(float dt) noexcept override;
};