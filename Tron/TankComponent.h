#pragma once

#include <memory>

#include "Component.h"
#include "Texture.h"
#include "MoveCommand.h"

class TileManagerComponent;

class TankComponent final : public Minigin::Component
{
public:
	explicit TankComponent(Minigin::GameObject* owner, float speed);
	virtual ~TankComponent() = default;

	TankComponent(const TankComponent&) = delete;
	TankComponent(TankComponent&&) noexcept = delete;	
	TankComponent& operator= (const TankComponent&) = delete;
	TankComponent& operator= (const TankComponent&&) noexcept = delete;

	float GetSpeed() const;
	void Move(MoveCommand::Direction direction);
	glm::ivec2 GetWorldPosition() const;

	virtual void Render() const override;

private:
	const float m_Speed;
	const std::unique_ptr<const Minigin::Texture> m_TankTexture;
	MoveCommand::Direction m_Direction;
	TileManagerComponent* m_TileManager;
};