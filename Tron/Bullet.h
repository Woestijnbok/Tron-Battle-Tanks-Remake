#pragma once

#include <vec2.hpp>
#include <chrono>

class Bullet final
{
public:
	explicit Bullet(const glm::ivec2& position, const glm::vec2& direction);
	~Bullet() = default;

	Bullet(const Bullet&) = delete;
	Bullet(Bullet&&) noexcept = delete;
	Bullet& operator=(const Bullet&) = delete;
	Bullet& operator=(const Bullet&&) = delete;

	void SetDirection(const glm::vec2& direction);
	const glm::vec2& GetDirection() const;
	bool Update();	// Returns true if it needs to be destroyed.
	glm::vec2 GetPosition() const;

	bool operator==(const Bullet& rhs) const;

private:
	const float m_Speed;	// Speed in meters per seconds (m/s)
	glm::vec2 m_Direction;
	glm::ivec2 m_Position;
	const std::chrono::steady_clock::time_point m_InitialTime;
	const std::chrono::duration<float> m_LifeTime;
};