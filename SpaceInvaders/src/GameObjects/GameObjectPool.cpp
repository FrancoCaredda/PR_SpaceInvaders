#include "GameObjectPool.h"

#include <stdexcept>
#include <iostream>

GameObjectPool* GameObjectPool::s_Instance = nullptr;

GameObjectPool::GameObjectPool()
{
	if (s_Instance)
		throw std::runtime_error::exception("There cannot be two instances of the GameObjectPool class");
	
	s_Instance = this;
	m_Projectiles.resize(m_ProjectilesNumber);
}

GameObjectPool::~GameObjectPool()
{
	for (Object* object : m_Objects)
		delete object;
}

Projectile* GameObjectPool::SpawnProjectile(Vector2 position) noexcept
{
	for (Projectile& projectile : m_Projectiles)
	{
		if (!projectile.Active)
		{
			projectile.Tranform.Position = position;
			projectile.Active = true;

			return &projectile;
		}
	}

	return nullptr;
}

void GameObjectPool::StartObjects() noexcept
{
	for (Object* object : m_Objects)
		object->Start();
}

void GameObjectPool::UpdateObjects(float dt) noexcept
{
	for (Object* object : m_Objects)
		object->Update(dt);
}

void GameObjectPool::UpdateProjectiles(float dt) noexcept
{
	for (Projectile& projectile : m_Projectiles)
	{
		if (projectile.Active)
		{
			projectile.Tranform.Position.y -= projectile.Velocity * dt;

			projectile.Lifetime -= dt;

			if (projectile.Lifetime < 0)
				projectile.Active = false;
		}
	}
}

GameObjectPool& GameObjectPool::GetInstance() noexcept
{
	return *s_Instance;
}
