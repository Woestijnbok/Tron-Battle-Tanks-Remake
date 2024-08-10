#pragma once

#include <vec2.hpp>

#include "TankComponent.h"
#include "Subject.h"

class PlayerTankComponent final : public TankComponent
{
public:
	explicit PlayerTankComponent(Minigin::GameObject* owner, TankManagerComponent* manager);
	virtual ~PlayerTankComponent() = default;

	PlayerTankComponent(const PlayerTankComponent&) = delete;
	PlayerTankComponent(PlayerTankComponent&&) noexcept = delete;
	PlayerTankComponent& operator= (const PlayerTankComponent&) = delete;
	PlayerTankComponent& operator= (const PlayerTankComponent&&) noexcept = delete;

	void SetBarrelRotation(int angle);

	virtual glm::vec2 GetFireDirection() const override;
	virtual void Render() const override;

private:
	const std::unique_ptr<const Minigin::Texture> m_TankTexture;	
	const std::unique_ptr<const Minigin::Texture> m_BarrelTexture;
	std::array<const glm::ivec2, 4> m_BarrelOffsets;
	const glm::ivec2 m_BarrelRotationPoint;	
	int m_BarrelRotation;	
};	