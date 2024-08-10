#include <iostream>
#include <random>

#include "BlueTankComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "PlayerTankComponent.h"
#include "TankManagerComponent.h"
#include "MoveCommand.h"

const std::chrono::duration<float> BlueTankComponent::m_FireRate{ 2.0f };
const int BlueTankComponent::m_Score{ 100 };

BlueTankComponent::BlueTankComponent(Minigin::GameObject* owner, TankManagerComponent* manager, const std::shared_ptr<Minigin::Texture>& tankTexture) :
	TankComponent{ owner, manager, 100.0f, 20, 3 },
	m_TankTexture{ tankTexture },
	m_FireTimePoint{ std::chrono::steady_clock::now() },
	m_CanFire{ true }
{

}

Minigin::Subject<int>& BlueTankComponent::OnDie()
{
	return m_OnDie;
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
	// Check player will return true if it found a player
	if (CheckPlayers())
	{
		// When he found a player he will try and shoot + face in the players direction
		Move(GetMoveDirection());
	}
	else
	{
		Roam();
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

bool BlueTankComponent::CheckPlayers()
{
	bool foundPlayer{ false };

	const glm::ivec2 position{ GetOwner()->GetLocalTransform().GetPosition() };

	for (PlayerTankComponent* player : GetManager()->GetPlayerTanks())
	{
		const glm::ivec2 playerPosition{ player->GetOwner()->GetLocalTransform().GetPosition() };

		if ((position.x == playerPosition.x) and (position.x % 50 == 0))
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

			foundPlayer = true;
			break;
		}
		else if ((position.y == playerPosition.y) and (position.y % 50 == 0))
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

			foundPlayer = true;
			break;
		}
	}

	if (!m_CanFire)
	{
		const auto timeDifference{ std::chrono::steady_clock::now() - m_FireTimePoint };
		if (timeDifference >= m_FireRate)
		{
			m_CanFire = true;
		}
	}

	if (foundPlayer)
	{
		if (m_CanFire)
		{
			Fire();
			m_CanFire = false;
			m_FireTimePoint = std::chrono::steady_clock::now();
		}
	}

	return foundPlayer;
}

void BlueTankComponent::Roam()
{
	const int tileSize{ GetManager()->GetTileSize() };
	const glm::ivec2 position{GetOwner()->GetLocalTransform().GetPosition() };

	// Get new random direction when at crossroad
	if ((position.x % tileSize == 0) and (position.y % tileSize == 0))	
	{	
		SetRandomDirection();	
	}

	Move(GetMoveDirection());
}

void BlueTankComponent::SetRandomDirection()	
{
	std::random_device random{};	
	std::mt19937 generator{ random() };
	std::uniform_int_distribution distributer{ 0, 3 };	

	MoveCommand::Direction direction{ distributer(generator) };	

	while (!GetManager()->CanMove(this, direction))	
	{
		direction = static_cast<MoveCommand::Direction>(distributer(generator));	
	}

	SetMoveDirection(direction);
}

void BlueTankComponent::Die()
{
	TankComponent::Die();

	m_OnDie.Notify(m_Score);
}
