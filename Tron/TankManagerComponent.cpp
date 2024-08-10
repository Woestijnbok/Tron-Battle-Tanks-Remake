#include <utility>
#include <vec2.hpp>
#include <iostream>
#include <algorithm>

#include "TankManagerComponent.h"
#include "BulletComponent.h"
#include "TankComponent.h"
#include "PlayerTankComponent.h"
#include "TileManagerComponent.h"
#include "BulletManagerComponent.h"

#include "Collision.h"
#include "GameObject.h"

TankManagerComponent::TankManagerComponent(Minigin::GameObject* owner) :
	Component{ owner },
	m_Tanks{},
	m_TileManager{},
	m_BulletManager{}
{

}

TankManagerComponent::~TankManagerComponent()
{
	TankComponent::SetManagerAlive(false);
}

void TankManagerComponent::SetManagers(TileManagerComponent* tileManager, BulletManagerComponent* bulletManager)
{
	m_TileManager = tileManager;
	m_BulletManager = bulletManager;
}

TileManagerComponent* TankManagerComponent::GetTileManager() const
{
	return m_TileManager;
}

BulletManagerComponent* TankManagerComponent::GetBulletManager() const
{
	return m_BulletManager;
}

void TankManagerComponent::AddTank(TankComponent* tank)
{
	if(std::ranges::find(m_Tanks, tank) == m_Tanks.end()) m_Tanks.push_back(tank);	
}

const std::vector<TankComponent*>& TankManagerComponent::GetTanks() const
{
	return m_Tanks;
}

std::vector<PlayerTankComponent*> TankManagerComponent::GetPlayerTanks() const
{
	std::vector<PlayerTankComponent*> players{};

	for (TankComponent* tank : m_Tanks)
	{
		PlayerTankComponent* player{ dynamic_cast<PlayerTankComponent*>(tank) };
		if (player != nullptr)
		{
			players.push_back(player);	
		}
	}

	return players;
}

void TankManagerComponent::CheckCollision(BulletComponent* bullet)
{
	if (bullet->GetOwner()->GetStatus() != ControllableObject::Status::Enabled) return;

	const glm::ivec2 bulletPosition{bullet->GetOwner()->GetLocalTransform().GetPosition() };

	for (TankComponent* tank : m_Tanks)
	{
		if (bullet->GetTank() != tank)
		{
			const std::pair<glm::ivec2, glm::ivec2> collisionRectangle{tank->GetCollisionRectangle() };
			if (Minigin::PointInsideRectangle(bulletPosition, collisionRectangle.first, collisionRectangle.second))
			{
				bullet->GetOwner()->SetStatus(ControllableObject::Status::Destroyed);
				tank->Hit();
			}
		}
	}
}

void TankManagerComponent::RemoveTank(TankComponent* tank)
{
	m_Tanks.erase(std::remove(m_Tanks.begin(), m_Tanks.end(), tank), m_Tanks.end());	
}

glm::ivec2 TankManagerComponent::GetRandomPosition() const
{
	return m_TileManager->GetRandomPosition();
}

bool TankManagerComponent::CanMove(TankComponent* tank, MoveCommand::Direction direction) const
{
	return m_TileManager->CanMove(tank, direction);
}

void TankManagerComponent::AddBullet(TankComponent* tank) const
{
	m_BulletManager->AddBullet(tank);
}