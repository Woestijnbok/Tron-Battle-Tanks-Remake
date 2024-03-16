#include "Command.h"

GameObjectCommand::GameObjectCommand(GameObject* gameObject) :
	Command(),
	m_GameObject{ gameObject }
{

}

GameObject* GameObjectCommand::GetGameObject()
{
	return m_GameObject;
}