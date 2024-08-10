#include <iostream>

#include "BlueTankComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "PlayerTankComponent.h"
#include "TankManagerComponent.h"

const std::chrono::duration<float> BlueTankComponent::m_FireRate{ 2.0f };

BlueTankComponent::BlueTankComponent(Minigin::GameObject* owner, TankManagerComponent* manager, const std::shared_ptr<Minigin::Texture>& tankTexture) :
	TankComponent{ owner, manager, 100.0f, 20, 3 },	
	m_TankTexture{ tankTexture },
	m_FireTimePoint{ std::chrono::steady_clock::now() }	,
	m_CanFire{ true }
{

}

glm::vec2 BlueTankComponent::GetFireDirection() const	
{
	glm::vec2 direction{};

	switch (GetMoveDirection())
	{
	case MoveCommand::Direction::Up:
		direction.y = 1.0f;
		break;
	case MoveCommand::Direction::Right:
		direction.x = 1.0f;
		break;
	case MoveCommand::Direction::Down:
		direction.y = -1.0f;
		break;
	case MoveCommand::Direction::Left:
		direction.x = -1.0f;
		break;
	}

	return direction;
}

void BlueTankComponent::Update()
{
	const glm::ivec2 position{ GetOwner()->GetLocalTransform().GetPosition() };
	bool checkForFire{ false };	

	for (PlayerTankComponent* player : GetManager()->GetPlayerTanks())
	{
		const glm::ivec2 playerPosition{ player->GetOwner()->GetLocalTransform().GetPosition() };	

		if (position.x == playerPosition.x)
		{
			// Above player
			if (position.y > playerPosition.y)
			{
				SetMoveDirection(MoveCommand::Direction::Down);
			}
			// Below player
			else
			{
				SetMoveDirection(MoveCommand::Direction::Up);
			}

			checkForFire = true;
			break;
		}
		else if (position.y == playerPosition.y)
		{
			// Right of player
			if (position.x > playerPosition.x)
			{
				SetMoveDirection(MoveCommand::Direction::Left);
			}
			// Left of player
			else
			{
				SetMoveDirection(MoveCommand::Direction::Right);
			}

			checkForFire = true;
			break;
		}
	}

	if(!m_CanFire)
	{
		const auto timeDifference{ std::chrono::steady_clock::now() - m_FireTimePoint };
		if (timeDifference >= m_FireRate) 
		{	
			m_CanFire = true;	
		}
	}

	if (checkForFire)
	{
		if (m_CanFire)
		{
			Fire();
			m_CanFire = false;
			m_FireTimePoint = std::chrono::steady_clock::now();	
			std::cout << "fired" << std::endl;
		}
	}
}

void BlueTankComponent::Render() const
{
	Minigin::Transform tankTransform{ GetOwner()->GetWorldTransform() };

	switch (GetMoveDirection())
	{
	case MoveCommand::Direction::Right:
		tankTransform.SetRotation(tankTransform.GetRotation() + 90);
		break;
	case MoveCommand::Direction::Down:
		tankTransform.SetRotation(tankTransform.GetRotation() + 180);
		break;
	case MoveCommand::Direction::Left:
		tankTransform.SetRotation(tankTransform.GetRotation() + 270);
		break;
	default:
		break;
	}

	m_TankTexture->Render(tankTransform);
}