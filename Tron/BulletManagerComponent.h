#pragma once

#include <vector>
#include <vec2.hpp>
#include <memory>

#include "Component.h"
#include "Texture.h"

class BulletComponent;
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

	void AddBullet(TankComponent* tank);
	Minigin::Texture* GetBulletTexture() const;
	void CheckCollision(BulletComponent* bullet);

private:
	std::vector<BulletComponent*> m_Bullets;
	std::unique_ptr<Minigin::Texture> m_BulletTexture;
	TileManagerComponent* m_TileManager;

};