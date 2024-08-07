#pragma once

#include <vector>
#include <vec2.hpp>
#include <memory>

#include "Component.h"
#include "Texture.h"

class Bullet;
class TileManagerComponent;
class TankComponent;

class BulletManagerComponent : public Minigin::Component
{
public:
	explicit BulletManagerComponent(Minigin::GameObject* owner, TileManagerComponent* tileManager);
	virtual ~BulletManagerComponent() = default;

	BulletManagerComponent(const BulletManagerComponent&) = delete;
	BulletManagerComponent(BulletManagerComponent&&) noexcept = delete;
	BulletManagerComponent& operator= (const BulletManagerComponent&) = delete;
	BulletManagerComponent& operator= (const BulletManagerComponent&&) noexcept = delete;

	void AddBullet(TankComponent* tank, const glm::vec2& position, const glm::vec2& direction);

	virtual void FixedUpdate() override;	
	virtual void Render() const;

private:
	std::vector<std::unique_ptr<Bullet>> m_Bullets;
	std::unique_ptr<Minigin::Texture> m_BulletTexture;
	TileManagerComponent* m_TileManager;

	void RemoveBullet(Bullet* bullet);
};