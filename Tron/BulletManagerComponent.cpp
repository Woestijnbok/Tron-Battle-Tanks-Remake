#include <format>

#include "BulletManagerComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "BulletComponent.h"
#include "TileManagerComponent.h"
#include "TankComponent.h"
#include "Scene.h"

BulletManagerComponent::BulletManagerComponent(Minigin::GameObject* owner, TileManagerComponent* tileManager) :
	Component{ owner },
	m_Bullets{},
	m_BulletTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Bullet.png") },
	m_TileManager{ tileManager }
{

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
}