#pragma once

#include <vec2.hpp>
#include "memory"

#include "TankComponent.h"
#include "Subject.h"
#include "Texture.h"

class PlayerTankComponent final : public TankComponent
{
public:
	explicit PlayerTankComponent(Minigin::GameObject* owner, TankManagerComponent* manager, const std::shared_ptr<Minigin::Texture>& tankTexture, const std::shared_ptr<Minigin::Texture>& barrelTexture, int lives);
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
	static int SetSharedLives(int lives);

private:
	const std::shared_ptr<const Minigin::Texture> m_TankTexture;	
	const std::shared_ptr<const Minigin::Texture> m_BarrelTexture;
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