#include "BulletManagerComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Bullet.h"
#include "TileManagerComponent.h"
#include "TankComponent.h"

BulletManagerComponent::BulletManagerComponent(Minigin::GameObject* owner, TileManagerComponent* tileManager) :
	Component{ owner },
	m_Bullets{},
	m_BulletTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Bullet.png") },
	m_TileManager{ tileManager }
{

}

void BulletManagerComponent::AddBullet(TankComponent* tank, const glm::vec2& position, const glm::vec2& direction)
{
	m_Bullets.push_back(std::make_unique<Bullet>(tank, position, direction));
}

void BulletManagerComponent::RemoveBullet(Bullet* bullet)
{
	m_Bullets.erase
	(
		std::remove_if
		(
			m_Bullets.begin(), m_Bullets.end(),
			[&bullet](const std::unique_ptr<Bullet>& object) -> bool
			{
				return *object.get() == *bullet;
			}
		), 
		m_Bullets.end()
	);
}

void BulletManagerComponent::FixedUpdate()
{
	std::vector<Bullet*> bulletsToRemove{};

	for (std::unique_ptr<Bullet>& bullet : m_Bullets)	
	{
		if(m_TileManager->CheckCollision(bullet.get())) bulletsToRemove.push_back(bullet.get());
		else if (bullet->Update()) bulletsToRemove.push_back(bullet.get());	
	}	

	for (Bullet* bullet : bulletsToRemove)
	{
		RemoveBullet(bullet);
	}
}

void BulletManagerComponent::Render() const
{
	Minigin::Transform transform{};

	for (const std::unique_ptr<Bullet>& bullet : m_Bullets)	
	{
		transform.SetPosition(bullet->GetPosition());
		m_BulletTexture->Render(transform);
	}
}