#pragma once

#include "Components.h"

class Object
{
public:
	Object() = default;
	~Object() = default;

	virtual void Start() noexcept = 0;
	virtual void Update(float dt) noexcept = 0;

	inline const Transform2D& GetTransform() const noexcept { return m_Transform; }
	inline const Sprite& GetSprite() const noexcept { return m_Sprite; }
	const Rectangle& GetBoundingBox() const noexcept;
protected:
	Transform2D m_Transform{};
	Sprite m_Sprite{};
private:
	mutable Rectangle m_BoundingBox{};
};