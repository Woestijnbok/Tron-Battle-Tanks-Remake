#include "TankComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TileManagerComponent.h"
#include "TimeManager.h"

TankComponent::TankComponent(Minigin::GameObject* owner, float speed) :
	Component{ owner },
	m_Speed{ speed },
	m_TankTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Tank.png") },
	m_Direction{ MoveCommand::Direction::Up },
	m_TileManager{ owner->GetScene()->GetGameObject("Tile Manager")->GetComponent<TileManagerComponent>() }		
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

void TankComponent::Render() const
{
	Minigin::Transform transform{ GetOwner()->GetWorldTransform() };
	const int currentRotatoin{ transform.GetRotation() };
	
	switch (m_Direction)
	{
	case MoveCommand::Direction::Right:
		transform.SetRotation(currentRotatoin + 90);
		break;
	case MoveCommand::Direction::Down:
		transform.SetRotation(currentRotatoin + 180);
		break;
	case MoveCommand::Direction::Left:
		transform.SetRotation(currentRotatoin + 270);
		break;
	default:
		break;
	}

	m_TankTexture->Render(transform);
}