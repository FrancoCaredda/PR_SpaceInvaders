#include "Game.h"
#include "Spaceship.h"

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

	m_Objects.push_back(new Spaceship());
}

void Game::Start()
{
	for (Object* object : m_Objects)
		object->Start();
}

void Game::Run()
{
	auto prev = std::chrono::high_resolution_clock::now();
	while (!WindowShouldClose())
	{
		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> deltaTime = now - prev;

		BeginDrawing();
		ClearBackground(Color{});

		for (Object* object : m_Objects)
			object->Update(deltaTime.count());

		m_Renderer.DrawObjects(m_Objects);

		EndDrawing();
	}
}

void Game::End()
{
	for (Object* object : m_Objects)
		delete object;

	CloseWindow();
}
