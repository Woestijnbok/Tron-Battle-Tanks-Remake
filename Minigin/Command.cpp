#include "Command.h"
#include "GameObject.h"

using namespace Minigin;

GameObjectCommand::GameObjectCommand(GameObject* gameObject) :
	Command(),
	m_GameObject{ gameObject }
{

}

GameObject* GameObjectCommand::GetGameObject()
{
	return m_GameObject;
}