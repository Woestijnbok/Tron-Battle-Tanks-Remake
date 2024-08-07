#include "FireCommand.h"
#include "TankComponent.h"

FireCommand::FireCommand(TankComponent* tank) :
	GameObjectCommand{ tank->GetOwner() },
	m_Tank{ tank }
{
	if (GetGameObject() == nullptr)
	{
		throw std::exception{ "FireCommand::FireCommand() - Move command has invalid game object" };	
	}

	if (m_Tank == nullptr)
	{
		throw std::exception{ "FireCommand::FireCommand() - Move command has invalid tank component." };	
	}
}

void FireCommand::Execute()
{
	m_Tank->Fire();
}

void FireCommand::Execute(const glm::vec2& /*axis*/)
{
	Execute();
}