#pragma once

#include <memory>
#include <array>

#include "Component.h"
#include "Texture.h"
#include "MoveCommand.h"
#include "Subject.h"

class TileManagerComponent;
class BulletManagerComponent;

class TankComponent final : public Minigin::Component
{
public:
	explicit TankComponent(Minigin::GameObject* owner, TileManagerComponent* tileManager, BulletManagerComponent* bulletManager, float speed);	
	virtual ~TankComponent() = default;

	TankComponent(const TankComponent&) = delete;
	TankComponent(TankComponent&&) noexcept = delete;	
	TankComponent& operator= (const TankComponent&) = delete;
	TankComponent& operator= (const TankComponent&&) noexcept = delete;

	float GetSpeed() const;
	void Move(MoveCommand::Direction direction);
	void SetBarrelRotation(int angle);
	void Fire();
	glm::vec2 GetDirection() const;
	Minigin::Subject<int>& OnLiveChange();
	Minigin::Subject<int>& OnScoreChange();

	virtual void Render() const override;

private:
	TileManagerComponent* m_TileManager;
	BulletManagerComponent* m_BulletManager;
	const float m_Speed;
	const std::unique_ptr<const Minigin::Texture> m_TankTexture;
	const std::unique_ptr<const Minigin::Texture> m_BarrelTexture;
	MoveCommand::Direction m_Direction;
	/*
	* @brief offsets for the barrel in each direction.
	* The order is up, right, left and down same as the enum.
	*/
	std::array<const glm::ivec2, 4> m_BarrelOffsets;
	const glm::ivec2 m_BarrelRotationPoint;
	int m_BarrelRotation;
	Minigin::Subject<int> m_OnLiveChange;
	Minigin::Subject<int> m_OnScoreChange;

};