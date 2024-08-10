#pragma once

#include "Command.h"
#include "PlayerTankComponent.h"

class PlayerTankComponent;

class FireCommand : public Minigin::GameObjectCommand
{
public:
	explicit FireCommand(PlayerTankComponent* tank);
	~FireCommand() = default;

	FireCommand(const FireCommand&) = default;
	FireCommand(FireCommand&&) noexcept = default;
	FireCommand& operator= (const FireCommand&) = delete;
	FireCommand& operator= (const FireCommand&&) = delete;

	virtual void Execute() override;
	virtual void Execute(const glm::vec2& axis) override;

private:
	PlayerTankComponent* m_Tank;

};