#include <glm.hpp>

#include "Bullet.h"
#include "TimeManager.h"
#include "TankComponent.h"

const std::chrono::duration<float> Bullet::m_LifeTime{ 5.0f };
const float Bullet::m_Speed{ 500.0f };
const int Bullet::m_MaxBounces{ 5 };

Bullet::Bullet(TankComponent* tank, const glm::ivec2& position, const glm::vec2& direction) :
	m_Tank{ tank },
	m_Direction{ direction },
	m_Position{ position },
	m_InitialTime{ std::chrono::steady_clock::now() }
{

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

glm::ivec2 Bullet::GetPosition() const	
{
	return m_Position;
}

bool Bullet::Bounce(Tile::Side side)
{
	glm::vec2 normal{};

	switch (side)
	{
	case Tile::Side::Top:
		normal.y = -1.0f;
		break;
	case Tile::Side::Right:
		normal.x = -1.0f;
		break;
	case Tile::Side::Bottom:
		normal.y = 1.0f;
		break;
	case Tile::Side::Left:
		normal.x = 1.0f;
		break;
	default:
		break;
	}

	normal = glm::normalize(normal);

	const glm::vec2 newDirection{ m_Direction - (2.0f * glm::dot(m_Direction, normal) * normal) };
	m_Direction = newDirection;

	++m_Bounces;

	return m_Bounces == m_MaxBounces;
}

void Bullet::SetPosition(const glm::ivec2& position)
{
	m_Position = position;
}

bool Bullet::operator==(const Bullet& rhs) const
{
	return m_InitialTime == rhs.m_InitialTime and m_Position == rhs.m_Position and m_Direction == rhs.m_Direction;
}
