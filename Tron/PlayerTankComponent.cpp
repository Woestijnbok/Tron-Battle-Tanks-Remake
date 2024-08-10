#include "PlayerTankComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

PlayerTankComponent::PlayerTankComponent(Minigin::GameObject* owner, TankManagerComponent* manager) :
	TankComponent{ owner, manager, 100.0f, 20, 3 },		
	m_OnScoreChange{},
	m_TankTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Red Tank.png") },	
	m_BarrelTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Barrel.png") },
	m_BarrelOffsets{ glm::ivec2{ 0, 4 }, glm::ivec2{ -4, 8 }, glm::ivec2{ 0, 12 }, glm::ivec2{ 4, 8 } },	
	m_BarrelRotationPoint{ 16, 8 },
	m_BarrelRotation{}
{

}

void PlayerTankComponent::SetBarrelRotation(int angle)
{
	m_BarrelRotation = angle;
}

Minigin::Subject<int>& PlayerTankComponent::OnScoreChange()
{
	return m_OnScoreChange;
}

glm::vec2 PlayerTankComponent::GetFireDirection() const
{
	const float radians{ m_BarrelRotation * (3.14f / 180.0f) };	
	glm::vec2 direction{};

	direction.x = std::sin(radians);
	direction.y = std::cos(radians);

	return direction;
}

void PlayerTankComponent::Render() const
{
	Minigin::Transform tankTransform{ GetOwner()->GetWorldTransform() };	
	Minigin::Transform barrelTransform{ tankTransform };	
	barrelTransform.SetRotation(m_BarrelRotation);	

	switch (GetMoveDirection())
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