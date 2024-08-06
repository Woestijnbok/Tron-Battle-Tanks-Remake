#include <exception>
#include <iostream>

#include "MoveCommand.h"
#include "GameObject.h"
#include "TankComponent.h"
#include "TimeManager.h"

MoveCommand::MoveCommand(Minigin::GameObject* object, Direction direction) :
	GameObjectCommand{ object },
	m_Direction{ direction },
	m_TankComponent{ GetGameObject()->GetComponent<TankComponent>() }	
{
	if (m_TankComponent == nullptr)	
	{
		throw std::exception{ "MoveCommand::MoveCommand() - Move command needs object with tank component." };
	}
}

void MoveCommand::Execute()
{
	m_TankComponent->Move(m_Direction);
}