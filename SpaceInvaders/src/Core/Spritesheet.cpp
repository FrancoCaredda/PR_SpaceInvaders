#include "Spritesheet.h"

#include <stdexcept>

Spritesheet::Spritesheet(Spritesheet&& spritesheet) noexcept
{
	m_Texture = spritesheet.m_Texture;
	m_CellSize = spritesheet.m_CellSize;

	spritesheet.m_Texture = Texture();
	spritesheet.m_CellSize = Vector2();
}

Spritesheet::~Spritesheet()
{
	if (IsTextureReady(m_Texture))
		UnloadTexture(m_Texture);
}

Spritesheet& Spritesheet::operator=(Spritesheet&& spritesheet) noexcept
{
	m_Texture = spritesheet.m_Texture;
	m_CellSize = spritesheet.m_CellSize;

	spritesheet.m_Texture = Texture();
	spritesheet.m_CellSize = Vector2();

	return *this;
}

SpritesheetLoader* SpritesheetLoader::s_Instance = nullptr;

SpritesheetLoader::SpritesheetLoader()
{
	if (s_Instance)
		throw std::runtime_error::exception("There cannot be two instances of the SpritesheetLoader class");
	
	s_Instance = this;
}

void SpritesheetLoader::Load(const std::filesystem::path& path, const Vector2& cellSize)
{
	if (!std::filesystem::exists(path))
		throw std::runtime_error::exception("The texture doesn't exist!");

	Texture2D texture = LoadTexture(path.string().c_str());

	if (!IsTextureReady(texture))
		throw std::runtime_error::exception("The texture isn't ready!");

	std::string filename = path.filename().string();
	
	m_Spritesheets[filename.substr(0, filename.find('.'))] = Spritesheet(texture, cellSize);
}

Spritesheet& SpritesheetLoader::GetSpritesheet(const std::string& key) noexcept
{
	return m_Spritesheets.at(key);
}

SpritesheetLoader& SpritesheetLoader::GetInstance() noexcept
{
	return *s_Instance;
}
