#include "Game.h"
#include "GameObjects/Spaceship.h"

#include "raylib.h"

#include <chrono>
#include <stdexcept>

Game* Game::s_Instance = nullptr;

Game::Game()
{
	if (s_Instance)
		throw std::runtime_error::exception("There cannot be two instances of the Game class");

	s_Instance = this;
}

void Game::Init()
{
	InitWindow(900, 450, "SpaceInvaders - Clone");
	SetTargetFPS(60);

	m_Renderer.SetFramebufferSize(Vector2{ 900, 450 });

	m_SpritesheetLoader.Load(std::filesystem::path(RESOURCE_DIR).concat("/SpaceInvaders_Ships.png"),
		Vector2{ 20, 20 });

	HideCursor();
	m_GameObjectPool.AddObject<Spaceship>();
}

void Game::Start()
{
	m_GameObjectPool.StartObjects();
}

void Game::Run()
{
	auto prev = std::chrono::high_resolution_clock::now();
	while (!WindowShouldClose())
	{
		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> deltaTime = now - prev;

		prev = now;

		BeginDrawing();
		ClearBackground(Color{});

		m_GameObjectPool.UpdateObjects(deltaTime.count());
		m_GameObjectPool.UpdateProjectiles(deltaTime.count());

		m_Renderer.DrawObjects(m_GameObjectPool.GetObjects());
		m_Renderer.DrawProjectiles(m_GameObjectPool.GetProjectiles());

		EndDrawing();
	}
}

void Game::End()
{
	CloseWindow();
}
