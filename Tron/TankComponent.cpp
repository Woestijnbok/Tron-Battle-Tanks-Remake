#include "TankComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TileManagerComponent.h"
#include "TimeManager.h"
#include "BulletManagerComponent.h"
#include "TankManagerComponent.h"

#include <iostream>

TankComponent::TankComponent(Minigin::GameObject* owner, TankManagerComponent* manager, float speed, int collisionSize) :
	Component{ owner },
	m_Manager{ manager },	
	m_Direction{ MoveCommand::Direction::Right },
	m_Speed{ speed },
	m_CollisionSize{ collisionSize },
	m_OnHit{},
	m_OnFire{}
{
	GetOwner()->SetLocalPosition(m_Manager->GetRandomPosition());	
}

TankComponent::~TankComponent()
{
	if (TankManagerComponent::Alive()) m_Manager->RemoveTank(this);
}

float TankComponent::GetMovementSpeed() const
{
	return m_Speed;
}

void TankComponent::Move(MoveCommand::Direction direction)
{
	if (!m_Manager->CanMove(this, direction)) return;	

	const glm::ivec2 oldPosition{ GetOwner()->GetLocalTransform().GetPosition() };	
	glm::ivec2 newPosition{ oldPosition };

	switch (direction)	
	{
	case MoveCommand::Direction::Up:
		newPosition.y += static_cast<int>(m_Speed * Minigin::TimeManager::Instance()->GetDeltaTime().count());
		break;
	case MoveCommand::Direction::Right:
		newPosition.x += static_cast<int>(m_Speed * Minigin::TimeManager::Instance()->GetDeltaTime().count());	
		break;
	case MoveCommand::Direction::Down:
		newPosition.y -= static_cast<int>(m_Speed * Minigin::TimeManager::Instance()->GetDeltaTime().count());
		break;
	case MoveCommand::Direction::Left:
		newPosition.x -= static_cast<int>(m_Speed * Minigin::TimeManager::Instance()->GetDeltaTime().count());
		break;
	default:
		break;
	}

	m_Direction = direction;
	GetOwner()->SetLocalPosition(newPosition);
	m_Manager->CheckBounds(this);
}

void TankComponent::Fire()
{
	m_Manager->AddBullet(this);
	m_OnFire.Notify();
}

Minigin::Rectangle TankComponent::GetCollisionRectangle() const
{
	const glm::ivec2 position{ GetOwner()->GetLocalTransform().GetPosition() };	

	const Minigin::Rectangle rectangle
	{
		position - m_CollisionSize / 2,
		position + m_CollisionSize / 2
	};

	return rectangle;	
}

Minigin::Subject<int>& TankComponent::OnHit()
{
	return m_OnHit;
}

Minigin::Subject<>& TankComponent::OnFire()	
{
	return m_OnFire;
}

MoveCommand::Direction TankComponent::GetMoveDirection() const
{
	return m_Direction;
}

void TankComponent::SetMoveDirection(MoveCommand::Direction direction)
{
	m_Direction = direction;
}

TankManagerComponent* TankComponent::GetManager() const
{
	return m_Manager;
}

void TankComponent::Die()
{
	GetOwner()->SetStatus(ControllableObject::Status::Destroyed);
}