#include "BulletManagerComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Bullet.h"

BulletManagerComponent::BulletManagerComponent(Minigin::GameObject* owner) :
	Component{ owner },
	m_Bullets{},
	m_BulletTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Bullet.png") }
{

}

void BulletManagerComponent::AddBullet(const glm::vec2& position, const glm::vec2& direction)
{
	m_Bullets.push_back(std::make_unique<Bullet>(position, direction));
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
		if (bullet->Update()) bulletsToRemove.push_back(bullet.get());
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