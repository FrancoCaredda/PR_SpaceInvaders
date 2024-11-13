#pragma once

#include "Object.h"

#include "raylib.h"

#include <vector>

class Renderer
{
public:
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) noexcept = delete;
	~Renderer() = default;

	void SetFramebufferSize(const Vector2& size);

	void DrawObjects(const std::vector<Object*>& objects);

	inline Vector2 GetFramebufferSize() const noexcept { return m_FramebufferSize; }
	inline float GetAspectRatio() const noexcept { return m_FramebufferSize.x / m_FramebufferSize.y; }
public:
	static Renderer& GetInstance() noexcept;
private:
	static Renderer* s_Instance;
	Vector2 m_FramebufferSize;
};