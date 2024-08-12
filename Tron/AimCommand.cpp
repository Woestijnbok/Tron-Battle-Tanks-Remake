#include "AimCommand.h"
#include "GameObject.h"
#include "PlayerTankComponent.h"

AimCommand::AimCommand(PlayerTankComponent* tank, bool controller) :
	Minigin::GameObjectCommand{ tank->GetOwner() },	
	m_Tank{ tank },	
	m_Controller{ controller }
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
	glm::vec2 startPoint{};	
	glm::vec2 endPoint{};	

	if (m_Controller)
	{
		startPoint = glm::vec2{ 0.0f, 0.0f };	
		endPoint = startPoint + (100.0f * axis);	
	}
	else
	{
		startPoint = GetGameObject()->GetWorldTransform().GetPosition();		
		endPoint = axis;		
	}

	int angle{ int(atan2(endPoint.x - startPoint.x, endPoint.y - startPoint.y) * (180.0f / 3.14f)) };	

	angle = 90 - angle;	

	angle = int(fmod((angle + 360.0), 360.0));	
	angle = int(fmod((450.0 - angle), 360.0));

	m_Tank->SetBarrelRotation(angle);
}