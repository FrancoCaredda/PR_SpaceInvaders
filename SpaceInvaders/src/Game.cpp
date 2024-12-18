#include "Game.h"

#include "Core/Physics.h"
#include "GameObjects/Alien.h"

#include "raylib.h"

#include <iostream>
#include <chrono>
#include <stdexcept>
#include <cstdlib>

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

	srand(time(0));

	m_Renderer.SetFramebufferSize(Vector2{ 900, 450 });

	m_SpritesheetLoader.Load(std::filesystem::path(RESOURCE_DIR).concat("/SpaceInvaders_Ships.png"),
		Vector2{ 16, 10 });
	m_SpritesheetLoader.Load(std::filesystem::path(RESOURCE_DIR).concat("/SpaceInvaders.png"),
		Vector2{ 15, 15 });

	HideCursor();
	m_Spaceship = m_GameObjectPool.AddObject<Spaceship>();

	for (int i = 0; i < m_AlienCount; i++)
		m_GameObjectPool.AddObject<Alien>();
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

		ProcessCollisions();
		ProcessBulletsCollisions();
		BeginDrawing();
		ClearBackground(Color{});

		m_GameObjectPool.UpdateObjects(deltaTime.count());
		m_GameObjectPool.UpdateProjectiles(deltaTime.count());

		m_Renderer.DrawObjects(m_GameObjectPool.GetObjects());
		m_Renderer.DrawProjectiles(m_GameObjectPool.GetProjectiles());

		EndDrawing();
	}
}

void Game::ProcessCollisions()
{
	const std::vector<Object*>& objects = m_GameObjectPool.GetObjects();

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i] != m_Spaceship)
		{
			Rectangle rect1 = m_Spaceship->GetBoundingBox();
			Rectangle rect2 = objects[i]->GetBoundingBox();

			if (Physics::AreRectanglesColliding(rect1, rect2))
				m_Spaceship->OnTriggerOverlapped(objects[i]);
		}
	}
}

void Game::ProcessBulletsCollisions()
{
	const std::vector<Object*>& objects = m_GameObjectPool.GetObjects();
	const std::vector<Projectile>& projectiles = m_GameObjectPool.GetProjectiles();

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i] != m_Spaceship)
		{
			for (const Projectile& projectile : projectiles)
			{
				Rectangle rect1 = projectile.GetBoundingBox();
				Rectangle rect2 = objects[i]->GetBoundingBox();

				if (Physics::AreRectanglesColliding(rect1, rect2))
				{
					objects[i]->OnShotTriggerOverlapped();
					objects[i]->Reset();
					const_cast<Projectile&>(projectile).Active = false;
				}
			}
		}
	}
}

void Game::End()
{
	CloseWindow();
}
