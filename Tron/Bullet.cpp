#include "Bullet.h"
#include "TimeManager.h"

Bullet::Bullet(const glm::ivec2& position, const glm::vec2& direction) :
	m_Speed{ 500.0f },
	m_Direction{ direction },
	m_Position{ position }
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

void Bullet::Update()
{
	const glm::vec2 movement{ Minigin::TimeManager::Instance()->GetFixedDeltaTime().count() * m_Speed * m_Direction };

	m_Position.x += static_cast<int>(movement.x);
	m_Position.y += static_cast<int>(movement.y);
}

glm::vec2 Bullet::GetPosition() const	
{
	return m_Position;
}