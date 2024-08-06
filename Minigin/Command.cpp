#include "Command.h"
#include "GameObject.h"

using namespace Minigin;

void Minigin::Command::Execute()
{

}

void Minigin::Command::Execute(const glm::vec2& /*axis*/)
{

}

GameObjectCommand::GameObjectCommand(GameObject* gameObject) :
	Command(),
	m_GameObject{ gameObject }
{

}

GameObject* GameObjectCommand::GetGameObject()
{
	return m_GameObject;
}