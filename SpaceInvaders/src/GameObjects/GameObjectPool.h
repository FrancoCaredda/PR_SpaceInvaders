#pragma once

#include "Core/Object.h"
#include "Projectile.h"

#include <type_traits>
#include <vector>

class GameObjectPool
{
public:
	GameObjectPool();
	GameObjectPool(const GameObjectPool&) = delete;
	GameObjectPool(GameObjectPool&&) noexcept = delete;
	~GameObjectPool();

	template<typename TObject>
	TObject* AddObject() noexcept
	{
		static_assert(constexpr std::is_base_of<Object, TObject>(), "TObject is not of type Object");
		TObject* object = new TObject();
		m_Objects.push_back(object);

		return object;
	}

	Projectile* SpawnProjectile(Vector2 position) noexcept;

	void StartObjects() noexcept;

	void UpdateObjects(float dt) noexcept;
	void UpdateProjectiles(float dt) noexcept;

	inline const std::vector<Object*>& GetObjects() const noexcept { return m_Objects; }
	inline const std::vector<Projectile>& GetProjectiles() const noexcept { return m_Projectiles; }
public:
	static GameObjectPool& GetInstance() noexcept;
private:
	static GameObjectPool* s_Instance;
private:
	std::vector<Object*> m_Objects;
	std::vector<Projectile> m_Projectiles;

	const int m_ProjectilesNumber = 100;
};