#include "PurpleTankComponent.h"
#include "Collision.h"
#include "TankManagerComponent.h"
#include "PlayerTankComponent.h"

const int PurpleTankComponent::m_Score{ 250 };

PurpleTankComponent::PurpleTankComponent(Minigin::GameObject* owner, TankManagerComponent* manager, const std::shared_ptr<Minigin::Texture>& tankTexture) :
	EnemyTankComponent{ owner, manager, tankTexture, 150.0f },
	m_Suicide{}
{

}

void PurpleTankComponent::Update()
{
	if (CheckPlayers())
	{
		Move(GetMoveDirection());
	}
	else
	{
		Roam();
	}

	PlayerTankComponent* hitPlayer{ CheckCollisionPlayers() };	
	if (hitPlayer != nullptr)	
	{
		m_Suicide = true;
		hitPlayer->Hit();
		Die();	
	}
}

PlayerTankComponent* PurpleTankComponent::CheckCollisionPlayers()
{
	PlayerTankComponent* hitPlayer{ nullptr };	

	for (PlayerTankComponent* player : GetManager()->GetPlayerTanks())
	{
		if (Minigin::RectanglesOverlap(this->GetCollisionRectangle(), player->GetCollisionRectangle()))
		{
			hitPlayer = player;
			break;
		}
	}

	return hitPlayer;
}

void PurpleTankComponent::Die()
{
	EnemyTankComponent::Die();

	if(!m_Suicide)OnDie().Notify(m_Score);
}