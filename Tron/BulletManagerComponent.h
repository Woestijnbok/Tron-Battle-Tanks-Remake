#pragma once

#include <vector>
#include <vec2.hpp>
#include <memory>

#include "Component.h"
#include "Texture.h"

class BulletComponent;
class TileManagerComponent;
class TankComponent;
class TankManagerComponent;

class BulletManagerComponent : public Minigin::Component
{
public:
	explicit BulletManagerComponent(Minigin::GameObject* owner);
	virtual ~BulletManagerComponent();

	BulletManagerComponent(const BulletManagerComponent&) = delete;
	BulletManagerComponent(BulletManagerComponent&&) noexcept = delete;
	BulletManagerComponent& operator= (const BulletManagerComponent&) = delete;
	BulletManagerComponent& operator= (const BulletManagerComponent&&) noexcept = delete;

	void SetManagers(TileManagerComponent* tileManager, TankManagerComponent* tankManager);
	void AddBullet(TankComponent* tank);
	void RemoveBullet(BulletComponent* bullet);
	Minigin::Texture* GetBulletTexture() const;
	void CheckCollision(BulletComponent* bullet);

	virtual void Update() override;

	static bool Alive();

private:
	std::vector<BulletComponent*> m_Bullets;
	std::unique_ptr<Minigin::Texture> m_BulletTexture;
	TileManagerComponent* m_TileManager;
	TankManagerComponent* m_TankManager;
	int m_Counter;

	static bool m_Alive;
};