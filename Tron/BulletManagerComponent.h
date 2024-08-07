#pragma once

#include <vector>
#include <vec2.hpp>
#include <memory>

#include "Component.h"
#include "Texture.h"

class Bullet;

class BulletManagerComponent : public Minigin::Component
{
public:
	explicit BulletManagerComponent(Minigin::GameObject* owner);
	virtual ~BulletManagerComponent() = default;

	BulletManagerComponent(const BulletManagerComponent&) = delete;
	BulletManagerComponent(BulletManagerComponent&&) noexcept = delete;
	BulletManagerComponent& operator= (const BulletManagerComponent&) = delete;
	BulletManagerComponent& operator= (const BulletManagerComponent&&) noexcept = delete;

	void AddBullet(const glm::vec2& position, const glm::vec2& direction);

	virtual void FixedUpdate() override;	
	virtual void Render() const;

private:
	std::vector<std::unique_ptr<Bullet>> m_Bullets;
	std::unique_ptr<Minigin::Texture> m_BulletTexture;

	void RemoveBullet(Bullet* bullet);
};