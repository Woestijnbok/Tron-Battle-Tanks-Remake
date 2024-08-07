#pragma once

#include <vector>
#include <vec2.hpp>
#include <memory>

#include "Component.h"
#include "Bullet.h"
#include "Texture.h"

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
	std::vector<Bullet> m_Bullets;
	std::unique_ptr<Minigin::Texture> m_BulletTexture;
};