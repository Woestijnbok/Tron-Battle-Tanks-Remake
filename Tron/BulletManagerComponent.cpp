#include "BulletManagerComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Transform.h"

BulletManagerComponent::BulletManagerComponent(Minigin::GameObject* owner) :
	Component{ owner },
	m_Bullets{},
	m_BulletTexture{ Minigin::Renderer::Instance()->CreateTexture(Minigin::ResourceManager::Instance()->GetTextureRootPath() / "Bullet.png") }
{

}

void BulletManagerComponent::AddBullet(const glm::vec2& position, const glm::vec2& direction)
{
	m_Bullets.emplace_back(position, direction);
}

void BulletManagerComponent::FixedUpdate()
{
	for (Bullet& bullet : m_Bullets)		
	{
		bullet.Update();
	}	
}

void BulletManagerComponent::Render() const
{
	Minigin::Transform transform{};

	for (const Bullet& bullet : m_Bullets)
	{
		transform.SetPosition(bullet.GetPosition());
		m_BulletTexture->Render(transform);
	}
}