#pragma once

#include <vec2.hpp>

#include "Command.h"

class PlayerTankComponent;	

class AimCommand : public Minigin::GameObjectCommand
{
public:
	AimCommand(PlayerTankComponent* tank);
	virtual ~AimCommand() = default;

	AimCommand(const AimCommand&) = delete;
	AimCommand(AimCommand&&) = delete;
	AimCommand& operator= (const AimCommand&) = delete;
	AimCommand& operator= (const AimCommand&&) = delete;

	virtual void Execute(const glm::vec2& axis) override;

private:
	PlayerTankComponent* m_Tank;

};