#include "Bullet.h"
#include "TimeManager.h"

Bullet::Bullet(const glm::ivec2& position, const glm::vec2& direction) :
	m_Speed{ 500.0f },
	m_Direction{ direction },
	m_Position{ position },
	m_InitialTime{ std::chrono::steady_clock::now() },
	m_LifeTime{ 5.0f }
{

}

void Bullet::SetDirection(const glm::vec2& direction)
{
	m_Direction = direction;
}

const glm::vec2& Bullet::GetDirection() const
{
	return m_Direction;
}

bool Bullet::Update()
{
	const auto timeDifference{ std::chrono::steady_clock::now() - m_InitialTime };
	if (timeDifference > m_LifeTime) return true;

	const glm::vec2 movement{ Minigin::TimeManager::Instance()->GetFixedDeltaTime().count() * m_Speed * m_Direction };

	m_Position.x += static_cast<int>(movement.x);
	m_Position.y += static_cast<int>(movement.y);

	return false;
}

glm::vec2 Bullet::GetPosition() const	
{
	return m_Position;
}

bool Bullet::operator==(const Bullet& rhs) const
{
	return m_InitialTime == rhs.m_InitialTime and m_Position == rhs.m_Position and m_Direction == rhs.m_Direction;
}
