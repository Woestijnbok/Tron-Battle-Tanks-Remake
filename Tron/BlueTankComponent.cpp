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
	EnemyTankComponent{ owner, manager, tankTexture, 75.0f },
	m_FireTimePoint{ std::chrono::steady_clock::now() },
	m_CanFire{ true }
{

}

void BlueTankComponent::Update()
{
	
	Reload();

	if (CheckPlayers())
	{
		TryFire();	
		Move(GetMoveDirection());
	}
	else
	{
		Roam();
	}
}

void BlueTankComponent::Reload()
{
	if (!m_CanFire)
	{
		const auto timeDifference{ std::chrono::steady_clock::now() - m_FireTimePoint };
		if (timeDifference >= m_FireRate)
		{
			m_CanFire = true;
		}
	}
}

void BlueTankComponent::TryFire()
{
	if (m_CanFire)
	{
		Fire();
		m_CanFire = false;
		m_FireTimePoint = std::chrono::steady_clock::now();
	}
}

void BlueTankComponent::Die()
{
	TankComponent::Die();

	OnDie().Notify(m_Score);
}