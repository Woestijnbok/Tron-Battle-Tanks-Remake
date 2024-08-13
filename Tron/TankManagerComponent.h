#pragma once

#include <vector>
#include <vec2.hpp>
#include <memory>

#include "Component.h"
#include "MoveCommand.h"
#include "Texture.h"
#include "Subject.h"
#include "Texture.h"

#include <memory>

class TankComponent;
class BulletComponent;
class PlayerTankComponent;
class TileManagerComponent;
class BulletManagerComponent;
class BlueTankComponent;
class PurpleTankComponent;

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
	PlayerTankComponent* CreatePlayerTank(const std::shared_ptr<Minigin::Texture>& tankTexture, const std::shared_ptr<Minigin::Texture>& barrelTexture, int lives);
	BlueTankComponent* CreateBlueTank(const std::shared_ptr<Minigin::Texture>& tankTexture);
	PurpleTankComponent* CreatePurpleTank(const std::shared_ptr<Minigin::Texture>& tankTexture);
	const std::vector<TankComponent*>& GetTanks() const;
	std::vector<PlayerTankComponent*> GetPlayerTanks() const;
	void CheckCollision(BulletComponent* bullet);
	void RemoveTank(TankComponent* tank);
	glm::ivec2 GetRandomPosition() const;
	bool CanMove(TankComponent* tank, MoveCommand::Direction direction) const;
	bool CanMove(const glm::ivec2& position, MoveCommand::Direction direction) const;
	void AddBullet(TankComponent* tank) const;
	int GetTileSize() const;
	Minigin::Subject<>& OnGameOver();
	Minigin::Subject<>& OnLevelCompleted();
	void CheckBounds(TankComponent* tank);
	void RemoveAllPlayers();

	virtual void Update() override;
	virtual void LateUpdate() override;

	static bool Alive();

private:
	std::vector<TankComponent*> m_Tanks;
	TileManagerComponent* m_TileManager;
	BulletManagerComponent* m_BulletManager;
	Minigin::Subject<> m_OnGameOver;
	Minigin::Subject<> m_OnLevelCompleted;

	static bool m_Alive;

	void CheckLevel();

};