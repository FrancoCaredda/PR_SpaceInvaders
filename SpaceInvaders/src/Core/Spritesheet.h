#pragma once

#include "raylib.h"

#include <filesystem>
#include <string>
#include <unordered_map>
#include <cstdint>

class Spritesheet
{
public:
	Spritesheet() = default;
	Spritesheet(const Texture2D& texture,
		const Vector2& cellSize) 
		: m_Texture(texture), m_CellSize(cellSize)
	{}

	Spritesheet(Spritesheet&& spritesheet) noexcept;
	~Spritesheet();

	inline const Texture2D& GetNative() const noexcept { return m_Texture; }
	inline Vector2 GetCellSize() const noexcept { return m_CellSize; }
	inline Vector2 GetTextureSize() const noexcept {
		return Vector2{ (float)m_Texture.width, (float)m_Texture.height }; }

	Spritesheet& operator=(Spritesheet&& spritesheet) noexcept;
private:
	Texture2D m_Texture;
	Vector2 m_CellSize;
};

class SpritesheetLoader
{
public:
	SpritesheetLoader();
	SpritesheetLoader(const SpritesheetLoader&) = delete;
	SpritesheetLoader(SpritesheetLoader&&) noexcept = delete;
	~SpritesheetLoader() = default;

	void Load(const std::filesystem::path& path,
		const Vector2& cellSize);

	Spritesheet& GetSpritesheet(const std::string& key) noexcept;
public:
	static SpritesheetLoader& GetInstance() noexcept;
private:
	static SpritesheetLoader* s_Instance;
	std::unordered_map<std::string, Spritesheet> m_Spritesheets;
};