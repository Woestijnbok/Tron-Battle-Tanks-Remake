#include <exception>
#include <iostream>

#include "MoveCommand.h"
#include "GameObject.h"
#include "TankComponent.h"

MoveCommand::MoveCommand(TankComponent* tank, Direction direction) :
	GameObjectCommand{ tank->GetOwner() },
	m_Direction{ direction },
	m_Tank{ tank }		
{
	if (GetGameObject() == nullptr)
	{
		throw std::exception{ "MoveCommand::MoveCommand() - Move command has invalid game object" };
	}

	if (m_Tank == nullptr)
	{
		throw std::exception{ "MoveCommand::MoveCommand() - Move command has invalid tank component." };
	}
}

void MoveCommand::Execute()
{
	m_Tank->Move(m_Direction);
}