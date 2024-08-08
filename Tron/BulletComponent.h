#pragma once

#include <vec2.hpp>
#include <chrono>

#include "TileComponent.h"
#include "Component.h"
#include "Texture.h"

class TankComponent;
class BulletManagerComponent;

class BulletComponent final : public Minigin::Component
{
public:
	explicit BulletComponent(Minigin::GameObject* owner, TankComponent* tank, BulletManagerComponent* manager);
	virtual ~BulletComponent() = default;

	BulletComponent(const BulletComponent&) = delete;	
	BulletComponent(BulletComponent&&) noexcept = delete;	
	BulletComponent& operator=(const BulletComponent&) = delete;	
	BulletComponent& operator=(const BulletComponent&&) = delete;	

	const glm::vec2& GetDirection() const;
	void Bounce(TileComponent::Side side);

	virtual void FixedUpdate() override;
	virtual void Render() const;

private:
	TankComponent* m_Tank;
	glm::vec2 m_Direction;
	const std::chrono::steady_clock::time_point m_InitialTime;
	int m_Bounces;
	Minigin::Texture* m_Texture;
	BulletManagerComponent* m_Manager;

	static const std::chrono::duration<float> m_LifeTime;
	static const float m_Speed;	// Speed in meters per seconds (m/s)
	static const int m_MaxBounces;
};