#pragma once

#include "Command.h"

class TankComponent;

class MoveCommand final : public Minigin::GameObjectCommand
{
public:
	enum class Direction
	{
		Up,
		Right,
		Down,
		Left
	};

	MoveCommand(Minigin::GameObject* object, Direction direction);
	virtual ~MoveCommand() = default;

	MoveCommand(const MoveCommand&) = delete;
	MoveCommand(MoveCommand&&) = delete;
	MoveCommand& operator= (const MoveCommand&) = delete;
	MoveCommand& operator= (const MoveCommand&&) = delete;

	virtual void Execute() override;

private:
	Direction m_Direction;
	TankComponent* m_TankComponent;

};