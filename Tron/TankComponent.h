#pragma once

#include <array>

#include "Component.h"
#include "MoveCommand.h"
#include "Subject.h"
#include "Collision.h"

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
	Minigin::Rectangle GetCollisionRectangle() const;
	Minigin::Subject<int>& OnHit();
	Minigin::Subject<>& OnFire();

	virtual void Hit() = 0;		
	virtual glm::vec2 GetFireDirection() const = 0;

protected:
	explicit TankComponent(Minigin::GameObject* owner, TankManagerComponent* manager, float speed, int collisionSize);

	MoveCommand::Direction GetMoveDirection() const;
	void SetMoveDirection(MoveCommand::Direction direction);
	TankManagerComponent* GetManager() const;

	virtual void Die();	

private:
	TankManagerComponent* m_Manager;
	MoveCommand::Direction m_Direction;	
	const float m_Speed;
	const int m_CollisionSize;
	Minigin::Subject<int> m_OnHit;	
	Minigin::Subject<> m_OnFire;

};