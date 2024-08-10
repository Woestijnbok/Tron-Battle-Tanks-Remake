#pragma once

#include <vector>
#include <vec2.hpp>

#include "Component.h"
#include "MoveCommand.h"
#include "Texture.h"

#include <memory>

class TankComponent;
class BulletComponent;
class PlayerTankComponent;
class TileManagerComponent;
class BulletManagerComponent;
class BlueTankComponent;

class TankManagerComponent final : public Minigin::Component
{
public:
	explicit TankManagerComponent(Minigin::GameObject* owner);
	virtual ~TankManagerComponent();

	TankManagerComponent(const TankManagerComponent&) = delete;
	TankManagerComponent(TankManagerComponent&&) noexcept = delete;
	TankManagerComponent& operator= (const TankManagerComponent&) = delete;
	TankManagerComponent& operator= (const TankManagerComponent&&) noexcept = delete;

	void SetManagers(TileManagerComponent* tileManager, BulletManagerComponent* bulletManager);	
	TileManagerComponent* GetTileManager() const;	
	BulletManagerComponent* GetBulletManager() const;
	PlayerTankComponent* CreatePlayerTank();
	BlueTankComponent* CreateBlueTank(const std::shared_ptr<Minigin::Texture>& tankTexture);
	const std::vector<TankComponent*>& GetTanks() const;
	std::vector<PlayerTankComponent*> GetPlayerTanks() const;
	void CheckCollision(BulletComponent* bullet);
	void RemoveTank(TankComponent* tank);
	glm::ivec2 GetRandomPosition() const;
	bool CanMove(TankComponent* tank, MoveCommand::Direction direction) const;
	void AddBullet(TankComponent* tank) const;

private:
	std::vector<TankComponent*> m_Tanks;
	TileManagerComponent* m_TileManager;
	BulletManagerComponent* m_BulletManager;

};