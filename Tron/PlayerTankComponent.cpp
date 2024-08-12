#include "PlayerTankComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TankManagerComponent.h"

int PlayerTankComponent::m_Counter{ 0 };
int PlayerTankComponent::m_SharedLives{ 0 };
bool PlayerTankComponent::m_LivesShared{ false };

PlayerTankComponent::PlayerTankComponent(Minigin::GameObject* owner, TankManagerComponent* manager, Minigin::Texture* tankTexture, Minigin::Texture* barrelTexture) :
	TankComponent{ owner, manager, 100.0f, 20 },
	m_TankTexture{ tankTexture },		
	m_BarrelTexture{ barrelTexture },	
	m_BarrelOffsets{ glm::ivec2{ 0, 4 }, glm::ivec2{ -4, 8 }, glm::ivec2{ 0, 12 }, glm::ivec2{ 4, 8 } },	
	m_BarrelRotationPoint{ 16, 8 },
	m_BarrelRotation{},
	m_Lives{ 3 }
{
	++m_Counter;
	if (m_SharedLives != 3) m_SharedLives = 3;
}

PlayerTankComponent::~PlayerTankComponent()
{
	--m_Counter;
}

void PlayerTankComponent::SetBarrelRotation(int angle)
{
	m_BarrelRotation = angle;
}

Minigin::Subject<>& PlayerTankComponent::OnDie()
{
	return m_OnDie;
}

int PlayerTankComponent::Lives() const
{
	return m_Lives;
}

glm::vec2 PlayerTankComponent::GetFireDirection() const
{
	const float radians{ m_BarrelRotation * (3.14f / 180.0f) };	
	glm::vec2 direction{};

	direction.x = std::sin(radians);
	direction.y = std::cos(radians);

	return direction;
}

void PlayerTankComponent::Hit()
{
	if (m_Lives > 0)	
	{
		if (m_LivesShared)
		{
			--m_SharedLives;
			OnHit().Notify(m_SharedLives);

			if (m_SharedLives == 0)
			{
				for (PlayerTankComponent* player : GetManager()->GetPlayerTanks())
				{
					player->Die();	
				}
			}
		}
		else
		{
			--m_Lives;
			OnHit().Notify(m_Lives);

			if (m_Lives == 0)
			{
				Die();	
			}
		}
	}
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

int PlayerTankComponent::SharedLives()
{
	return m_SharedLives;
}

int PlayerTankComponent::Counter()
{
	return m_Counter;
}

void PlayerTankComponent::SetLivesShared(bool shared)
{
	m_LivesShared = shared;
}

void PlayerTankComponent::Die()
{
	TankComponent::Die();

	m_OnDie.Notify();
}