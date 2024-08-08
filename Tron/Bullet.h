#pragma once

#include <vec2.hpp>
#include <chrono>

#include "TileComponent.h"

class TankComponent;

class Bullet final
{
public:
	explicit Bullet(TankComponent* tank, const glm::ivec2& position, const glm::vec2& direction);
	~Bullet() = default;

	Bullet(const Bullet&) = delete;
	Bullet(Bullet&&) noexcept = delete;
	Bullet& operator=(const Bullet&) = delete;
	Bullet& operator=(const Bullet&&) = delete;

	const glm::vec2& GetDirection() const;
	bool Update();	// Returns true if it needs to be destroyed.
	glm::ivec2 GetPosition() const;
	bool Bounce(TileComponent::Side side);	
	void SetPosition(const glm::ivec2& position);

	bool operator==(const Bullet& rhs) const;

private:
	TankComponent* m_Tank;
	glm::vec2 m_Direction;
	glm::ivec2 m_Position;
	const std::chrono::steady_clock::time_point m_InitialTime;
	int m_Bounces;

	static const std::chrono::duration<float> m_LifeTime;
	static const float m_Speed;	// Speed in meters per seconds (m/s)
	static const int m_MaxBounces;
};