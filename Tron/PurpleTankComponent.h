#pragma once

#include "EnemyTankComponent.h"

class PlayerTankComponent;

class PurpleTankComponent : public EnemyTankComponent
{
public:
	explicit PurpleTankComponent(Minigin::GameObject* owner, TankManagerComponent* manager, const std::shared_ptr<Minigin::Texture>& tankTexture);
	virtual ~PurpleTankComponent() = default;

	PurpleTankComponent(const PurpleTankComponent&) = delete;
	PurpleTankComponent(PurpleTankComponent&&) noexcept = delete;
	PurpleTankComponent& operator= (const PurpleTankComponent&) = delete;
	PurpleTankComponent& operator= (const PurpleTankComponent&&) noexcept = delete;

	virtual void Update() override;

private:
	bool m_Suicide;

	static const int m_Score;

	PlayerTankComponent* CheckCollisionPlayers();

	virtual void Die();
};