#include "EnemyTankComponent.h"

#include <iostream>
#include <random>

#include "GameObject.h"
#include "Scene.h"
#include "PlayerTankComponent.h"
#include "TankManagerComponent.h"
#include "MoveCommand.h"

int EnemyTankComponent::m_Counter{ 0 };

EnemyTankComponent::EnemyTankComponent(Minigin::GameObject* owner, TankManagerComponent* manager, const std::shared_ptr<Minigin::Texture>& tankTexture, float speed) :
	TankComponent{ owner, manager, speed, 20 },	
	m_TankTexture{ tankTexture },
	m_OnDie{},
	m_Lives{ 3 }
{
	++m_Counter;
}

EnemyTankComponent::~EnemyTankComponent()
{
	--m_Counter;
}

Minigin::Subject<int>& EnemyTankComponent::OnDie()
{
	return m_OnDie;
}

glm::vec2 EnemyTankComponent::GetFireDirection() const
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

void EnemyTankComponent::Hit()
{
	if (m_Lives > 0)	
	{
		--m_Lives;	
		OnHit().Notify(m_Lives);
		if (m_Lives == 0) Die();
	}
}

void EnemyTankComponent::Render() const
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

int EnemyTankComponent::Counter()
{
	return m_Counter;
}

bool EnemyTankComponent::CheckPlayers()
{
	bool foundPlayer{ false };

	const glm::ivec2 tankPosition{ GetOwner()->GetLocalTransform().GetPosition() };

	for (PlayerTankComponent* player : GetManager()->GetPlayerTanks())
	{
		const glm::ivec2 playerPosition{ player->GetOwner()->GetLocalTransform().GetPosition() };

		if ((tankPosition.x == playerPosition.x) and (tankPosition.x % 50 == 0))
		{
			// Above player
			if (tankPosition.y > playerPosition.y)
			{
				if (CanSeePlayer(tankPosition, playerPosition, MoveCommand::Direction::Down))
				{
					SetMoveDirection(MoveCommand::Direction::Down);		
					foundPlayer = true;	
					break;	
				}
			}
			// Below player
			else
			{
				if (CanSeePlayer(tankPosition, playerPosition, MoveCommand::Direction::Up))		
				{
					SetMoveDirection(MoveCommand::Direction::Up);		
					foundPlayer = true;	
					break;
				}
			}	
		}
		else if ((tankPosition.y == playerPosition.y) and (tankPosition.y % 50 == 0))	
		{
			// Right of player	
			if (tankPosition.x > playerPosition.x)	
			{
				if (CanSeePlayer(tankPosition, playerPosition, MoveCommand::Direction::Left))			
				{
					SetMoveDirection(MoveCommand::Direction::Left);		
					foundPlayer = true;	
					break;
				}
			}
			// Left of player
			else
			{
				if (CanSeePlayer(tankPosition, playerPosition, MoveCommand::Direction::Right))		
				{
					SetMoveDirection(MoveCommand::Direction::Right);	
					foundPlayer = true;
					break;
				}
			}
		}
	}

	return foundPlayer;
}

void EnemyTankComponent::Roam()
{
	const int tileSize{ GetManager()->GetTileSize() };
	const glm::ivec2 position{ GetOwner()->GetLocalTransform().GetPosition() };

	// Get new random direction when at crossroad
	if ((position.x % tileSize == 0) and (position.y % tileSize == 0))
	{
		SetRandomDirection();
	}

	Move(GetMoveDirection());
}

void EnemyTankComponent::SetRandomDirection()
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

bool EnemyTankComponent::CanSeePlayer(const glm::ivec2& tankPosition, const glm::ivec2& playerPosition, MoveCommand::Direction direction) const
{
	bool canSee{ false };	
	int numberOfTilesToCheck{};

	switch (direction)
	{
	case MoveCommand::Direction::Up:
	case MoveCommand::Direction::Down:	
		numberOfTilesToCheck = std::abs(playerPosition.y - tankPosition.y) / GetManager()->GetTileSize();
		break;
	case MoveCommand::Direction::Right:	
	case MoveCommand::Direction::Left:	
		numberOfTilesToCheck = std::abs(playerPosition.x - tankPosition.x) / GetManager()->GetTileSize();
		break;
	default:
		return canSee;
		break;
	}

	if (numberOfTilesToCheck == 0)	
	{	
		canSee = true;		
	}
	else
	{
		int tilesChecked{ 0 };
		do
		{
			glm::ivec2 positionToCheck{ tankPosition.x, tankPosition.y };		

			switch (direction)
			{
			case MoveCommand::Direction::Up:
				positionToCheck.y += (GetManager()->GetTileSize() * (tilesChecked + 1));
				if (positionToCheck == playerPosition) --positionToCheck.y;
				break;
			case MoveCommand::Direction::Right:
				positionToCheck.x += (GetManager()->GetTileSize() * (tilesChecked + 1));
				if (positionToCheck == playerPosition) --positionToCheck.x;
				break;
			case MoveCommand::Direction::Down:
				positionToCheck.y -= (GetManager()->GetTileSize() * (tilesChecked + 1));
				if (positionToCheck == playerPosition) ++positionToCheck.y;
				break;
			case MoveCommand::Direction::Left:
				positionToCheck.x -= (GetManager()->GetTileSize() * (tilesChecked + 1));
				if (positionToCheck == playerPosition) ++positionToCheck.x;
				break;
			default:
				break;
			}

			canSee = GetManager()->CanMove(positionToCheck, direction);	

			++tilesChecked;
		} 
		while (tilesChecked < numberOfTilesToCheck and canSee);
	}

	return canSee;
}