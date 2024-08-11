#include <format>
#include <iostream>

#include "BulletManagerComponent.h"
#include "BulletComponent.h"
#include "TileManagerComponent.h"
#include "TankComponent.h"
#include "TankManagerComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Scene.h"

bool BulletManagerComponent::m_Alive{ false };

BulletManagerComponent::BulletManagerComponent(Minigin::GameObject* owner) :
	Component{ owner },
	m_Bullets{},
	m_BulletTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Bullet.png") },
	m_TileManager{},
	m_TankManager{},
	m_Counter{ 0 }
{
	m_Alive = true;
}

BulletManagerComponent::~BulletManagerComponent()
{
	for (BulletComponent* bullet : m_Bullets)
	{
		bullet->GetOwner()->SetStatus(ControllableObject::Status::Destroyed);
		bullet->SetStatus(ControllableObject::Status::Destroyed);
	}

	m_Alive = false;
}

void BulletManagerComponent::SetManagers(TileManagerComponent* tileManager, TankManagerComponent* tankManager)
{
	m_TileManager = tileManager;
	m_TankManager = tankManager;
}

void BulletManagerComponent::AddBullet(TankComponent* tank)
{
	Minigin::Scene* scene{ GetOwner()->GetScene() };

	Minigin::GameObject* object{ scene->CreateGameObject(std::format("Bullet {}", m_Counter)) };
	object->SetParent(GetOwner());
	BulletComponent* bullet{ object->CreateComponent<BulletComponent>(tank, this) };

	m_Bullets.push_back(bullet);

	++m_Counter;
}

void BulletManagerComponent::RemoveBullet(BulletComponent* bullet)
{
	m_Bullets.erase(std::remove(m_Bullets.begin(), m_Bullets.end(), bullet), m_Bullets.end());
}

Minigin::Texture* BulletManagerComponent::GetBulletTexture() const
{
	return m_BulletTexture.get();	
}

void BulletManagerComponent::CheckCollision(BulletComponent* bullet)
{
	if(TileManagerComponent::Alive())m_TileManager->CheckCollision(bullet);
	else
	{
		std::cout << "TileManager dead";
	}
	if(TankManagerComponent::Alive())m_TankManager->CheckCollision(bullet);
	else
	{
		std::cout << "Tank Manager dead";
	}
}

void BulletManagerComponent::Update()
{
	if (!m_Alive) m_Alive = true;
}

bool BulletManagerComponent::Alive()
{
	return m_Alive;
}
