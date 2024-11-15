#pragma once

#include "GameObjects/GameObjectPool.h"
#include "Core/Renderer.h"
#include "Core/Spritesheet.h"

#include <vector>

class Game
{
public:
	Game();
	Game(const Game&) = delete;
	Game(Game&&) noexcept = delete;
	~Game() = default;

	void Init();
	void Start();
	void Run();
	void End();
private:
	static Game* s_Instance;

	SpritesheetLoader m_SpritesheetLoader;
	Renderer m_Renderer;

	GameObjectPool m_GameObjectPool;
};