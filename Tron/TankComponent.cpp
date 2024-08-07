#include "TankComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TileManagerComponent.h"
#include "TimeManager.h"
#include "BulletManagerComponent.h"

TankComponent::TankComponent(Minigin::GameObject* owner, TileManagerComponent* tileManager, BulletManagerComponent* bulletManager, float speed) :
	Component{ owner },
	m_TileManager{ tileManager },
	m_BulletManager{ bulletManager },
	m_Speed{ speed },
	m_TankTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Red Tank.png") },
	m_BarrelTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Barrel.png") },
	m_Direction{ MoveCommand::Direction::Up },
	m_BarrelOffsets{ glm::ivec2{ 0, 4 }, glm::ivec2{ -4, 8 }, glm::ivec2{ 0, 12 }, glm::ivec2{ 4, 8 } },
	m_BarrelRotationPoint{ 16, 8 },
	m_BarrelRotation{}
{
	GetOwner()->SetLocalPosition(m_TileManager->GetStartPosition());			
}

float TankComponent::GetSpeed() const
{
	return m_Speed;
}

void TankComponent::Move(MoveCommand::Direction direction)
{
	if (!m_TileManager->CanMove(this, direction)) return;

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
}

glm::ivec2 TankComponent::GetWorldPosition() const
{
	return GetOwner()->GetWorldTransform().GetPosition();
}

void TankComponent::SetBarrelRotation(int angle)
{
	m_BarrelRotation = angle;
}

void TankComponent::Fire() const
{
	m_BulletManager->AddBullet(GetOwner()->GetWorldTransform().GetPosition(), glm::vec2{ 1.0f, 0.0f });
}

void TankComponent::Render() const
{
	Minigin::Transform tankTransform{ GetOwner()->GetWorldTransform() };
	Minigin::Transform barrelTransform{ tankTransform };
	barrelTransform.SetRotation(m_BarrelRotation);
	
	switch (m_Direction)
	{
	case MoveCommand::Direction::Up:
		barrelTransform.SetPosition(barrelTransform.GetPosition() + m_BarrelOffsets.at(0));		
		break;
	case MoveCommand::Direction::Right:	
		tankTransform.SetRotation(tankTransform.GetRotation() + 90);
		barrelTransform.SetPosition(barrelTransform.GetPosition() + m_BarrelOffsets.at(1));	
		break;
	case MoveCommand::Direction::Down:	
		tankTransform.SetRotation(tankTransform.GetRotation() + 180);	
		barrelTransform.SetPosition(barrelTransform.GetPosition() + m_BarrelOffsets.at(2));	
		break;
	case MoveCommand::Direction::Left:	
		tankTransform.SetRotation(tankTransform.GetRotation() + 270);		
		barrelTransform.SetPosition(barrelTransform.GetPosition() + m_BarrelOffsets.at(3));	
		break;
	default:
		break;
	}

	m_TankTexture->Render(tankTransform);
	m_BarrelTexture->Render(barrelTransform, m_BarrelRotationPoint);
}