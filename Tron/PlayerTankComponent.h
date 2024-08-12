#pragma once

#include <vec2.hpp>

#include "TankComponent.h"
#include "Subject.h"

class PlayerTankComponent final : public TankComponent
{
public:
	explicit PlayerTankComponent(Minigin::GameObject* owner, TankManagerComponent* manager, Minigin::Texture* tankTexture, Minigin::Texture* barrelTexture);
	virtual ~PlayerTankComponent();

	PlayerTankComponent(const PlayerTankComponent&) = delete;
	PlayerTankComponent(PlayerTankComponent&&) noexcept = delete;
	PlayerTankComponent& operator= (const PlayerTankComponent&) = delete;
	PlayerTankComponent& operator= (const PlayerTankComponent&&) noexcept = delete;

	void SetBarrelRotation(int angle);
	Minigin::Subject<>& OnDie();
	int Lives() const;

	virtual glm::vec2 GetFireDirection() const override;
	virtual void Hit() override;
	virtual void Render() const override;

	static int SharedLives();	
	static int Counter();
	static void SetLivesShared(bool shared);

private:
	const std::unique_ptr<const Minigin::Texture> m_TankTexture;	
	const std::unique_ptr<const Minigin::Texture> m_BarrelTexture;
	std::array<const glm::ivec2, 4> m_BarrelOffsets;
	const glm::ivec2 m_BarrelRotationPoint;	
	int m_BarrelRotation;
	Minigin::Subject<> m_OnDie;
	int m_Lives;

	static int m_Counter;
	static int m_SharedLives;
	static bool m_LivesShared;

	virtual void Die() override;
};	