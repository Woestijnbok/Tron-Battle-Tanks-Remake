#pragma once

#include <chrono>

#include "EnemyTankComponent.h"

class PlayerTankComponent;

class BlueTankComponent final : public EnemyTankComponent
{
public:
	explicit BlueTankComponent(Minigin::GameObject* owner, TankManagerComponent* manager, const std::shared_ptr<Minigin::Texture>& tankTexture);	
	virtual ~BlueTankComponent() = default;

	BlueTankComponent(const BlueTankComponent&) = delete;
	BlueTankComponent(BlueTankComponent&&) noexcept = delete;
	BlueTankComponent& operator= (const BlueTankComponent&) = delete;
	BlueTankComponent& operator= (const BlueTankComponent&&) noexcept = delete;

	virtual void Update() override;

private:
	std::chrono::steady_clock::time_point m_FireTimePoint;
	bool m_CanFire;

	static const std::chrono::duration<float> m_FireRate;
	static const int m_Score;

	void Reload();
	void TryFire();

	virtual void Die();

};

