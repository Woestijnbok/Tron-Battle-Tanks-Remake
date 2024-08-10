#pragma once

#include <memory>
#include <array>
#include <utility>

#include "Component.h"
#include "Texture.h"
#include "MoveCommand.h"
#include "Subject.h"

class TileManagerComponent;
class BulletManagerComponent;
class TankManagerComponent;

class TankComponent : public Minigin::Component
{
public:	
	virtual ~TankComponent();

	TankComponent(const TankComponent&) = delete;
	TankComponent(TankComponent&&) noexcept = delete;	
	TankComponent& operator= (const TankComponent&) = delete;
	TankComponent& operator= (const TankComponent&&) noexcept = delete;

	float GetMovementSpeed() const;
	void Move(MoveCommand::Direction direction);
	void Fire();
	std::pair<glm::ivec2, glm::ivec2> GetCollisionRectangle() const;
	Minigin::Subject<int>& OnLivesChange();
	Minigin::Subject<>& OnFire();
	int GetLives() const;
	void Hit();		

	virtual glm::vec2 GetFireDirection() const = 0;

	static void SetManagerAlive(bool alive);

protected:
	explicit TankComponent(Minigin::GameObject* owner, TankManagerComponent* manager, float speed, int collisionSize, int lives);

	MoveCommand::Direction GetMoveDirection() const;
	void SetMoveDirection(MoveCommand::Direction direction);
	TankManagerComponent* GetManager() const;

private:
	TankManagerComponent* m_Manager;
	MoveCommand::Direction m_Direction;	
	const float m_Speed;
	const int m_CollisionSize;
	int m_Lives;
	Minigin::Subject<int> m_OnLivesChange;	
	Minigin::Subject<> m_OnFire;

	static bool m_ManagerAlive;
};