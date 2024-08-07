#pragma once

#include <vec2.hpp>

class Bullet final
{
public:
	explicit Bullet(const glm::ivec2& position, const glm::vec2& direction);
	~Bullet() = default;

	Bullet(const Bullet&) = default;
	Bullet(Bullet&&) noexcept = default;
	Bullet& operator= (const Bullet&) = delete;
	Bullet& operator= (const Bullet&&) = delete;

	void SetDirection(const glm::vec2& direction);
	const glm::vec2& GetDirection() const;
	void Update();
	glm::vec2 GetPosition() const;

private:
	const float m_Speed;	// Speed in m/s
	glm::vec2 m_Direction;
	glm::ivec2 m_Position;

};