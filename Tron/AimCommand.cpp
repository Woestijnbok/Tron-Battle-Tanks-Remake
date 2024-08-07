#include "AimCommand.h"
#include "GameObject.h"
#include "TankComponent.h"

AimCommand::AimCommand(TankComponent* tank) :
	Minigin::GameObjectCommand{ tank->GetOwner() },
	m_Tank{ tank }
{
	if (GetGameObject() == nullptr)		
	{
		throw std::exception{ "AimCommand::AimCommand() - Move command has invalid game object" };
	}

	if (m_Tank == nullptr)
	{
		throw std::exception{ "AimCommand::AimCommand() - Move command has invalid tank component." };
	}
}

void AimCommand::Execute(const glm::vec2& axis)	
{
	const glm::ivec2 startPoint{ GetGameObject()->GetWorldTransform().GetPosition() };
	int angle{ int(atan2(axis.x - static_cast<int>(startPoint.x), axis.y - static_cast<int>(startPoint.y)) * (180.0f / 3.14f)) };

	angle = 90 - angle;	

	angle = int(fmod((angle + 360.0), 360.0));	
	angle = int(fmod((450.0 - angle), 360.0));

	m_Tank->SetBarrelRotation(angle);
}