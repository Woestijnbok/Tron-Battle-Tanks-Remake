#include <glm.hpp>

#include "BulletComponent.h"
#include "TimeManager.h"
#include "TankComponent.h"
#include "GameObject.h"
#include "BulletManagerComponent.h"

const std::chrono::duration<float> BulletComponent::m_LifeTime{ 10.0f };
const float BulletComponent::m_Speed{ 400.0f };
const int BulletComponent::m_MaxBounces{ 5 };

BulletComponent::BulletComponent(Minigin::GameObject* owner, TankComponent* tank, BulletManagerComponent* manager) :
	Component{ owner },
	m_Tank{ tank },
	m_Direction{ tank->GetDirection() },
	m_InitialTime{ std::chrono::steady_clock::now() },
	m_Bounces{},
	m_Texture{ manager->GetBulletTexture() },
	m_Manager{ manager }
{
	GetOwner()->SetLocalPosition(m_Tank->GetOwner()->GetLocalTransform().GetPosition());
}

const glm::vec2& BulletComponent::GetDirection() const
{
	return m_Direction;
}

void BulletComponent::Bounce(TileComponent::Side side)
{
	glm::vec2 normal{};

	switch (side)
	{
	case TileComponent::Side::Top:
		normal.y = 1.0f;
		break;
	case TileComponent::Side::Right:
		normal.x = 1.0f;
		break;
	case TileComponent::Side::Bottom:
		normal.y = -1.0f;
		break;
	case TileComponent::Side::Left:
		normal.x = -1.0f;
		break;
	default:
		break;
	}

	normal = glm::normalize(normal);

	const glm::vec2 newDirection{ m_Direction - (2.0f * glm::dot(m_Direction, normal) * normal) };
	m_Direction = newDirection;

	++m_Bounces;
	if (m_Bounces == m_MaxBounces)
	{
		SetStatus(Status::Destroyed);
	}
}

void BulletComponent::FixedUpdate()
{
	const auto timeDifference{ std::chrono::steady_clock::now() - m_InitialTime };

	if (timeDifference > m_LifeTime) 
	{
		SetStatus(Status::Destroyed);	
	}
	else
	{
		m_Manager->CheckCollision(this);

		const glm::ivec2 oldPosition{ GetOwner()->GetLocalTransform().GetPosition() };	
		const glm::vec2 movement{ Minigin::TimeManager::Instance()->GetFixedDeltaTime().count() * m_Speed * m_Direction };	
		const glm::ivec2 newPosition{ oldPosition + glm::ivec2{ movement } };	

		GetOwner()->SetLocalPosition(newPosition);	
	}
}

void BulletComponent::Render() const
{
	m_Texture->Render(GetOwner()->GetWorldTransform());
}