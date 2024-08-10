#include <format>

#include "BulletManagerComponent.h"
#include "BulletComponent.h"
#include "TileManagerComponent.h"
#include "TankComponent.h"
#include "TankManagerComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Scene.h"

BulletManagerComponent::BulletManagerComponent(Minigin::GameObject* owner) :	
	Component{ owner },
	m_Bullets{},
	m_BulletTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Bullet.png") },
	m_TileManager{},
	m_TankManager{}
{

}

void BulletManagerComponent::SetManagers(TileManagerComponent* tileManager, TankManagerComponent* tankManager)
{
	m_TileManager = tileManager;
	m_TankManager = tankManager;
}

TileManagerComponent* BulletManagerComponent::GetTileManager() const
{
	return m_TileManager;
}

TankManagerComponent* BulletManagerComponent::GetTankManager() const
{
	return m_TankManager;
}

void BulletManagerComponent::AddBullet(TankComponent* tank)
{
	Minigin::Scene* scene{ GetOwner()->GetScene() };

	Minigin::GameObject* object{ scene->CreateGameObject(std::format("Bullet {}", m_Bullets.size() - 1)) };
	object->SetParent(GetOwner());
	BulletComponent* bullet{ object->CreateComponent<BulletComponent>(tank, this) };

	m_Bullets.push_back(bullet);	
}

Minigin::Texture* BulletManagerComponent::GetBulletTexture() const
{
	return m_BulletTexture.get();	
}

void BulletManagerComponent::CheckCollision(BulletComponent* bullet)
{
	m_TileManager->CheckCollision(bullet);
	m_TankManager->CheckCollision(bullet);	
}