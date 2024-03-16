#include <iostream>
#include <format>

#include "CustumCommands.h"
#include "GameObject.h"

void TestCommand::Execute() const
{
	std::cout << "Test command fired" << std::endl;
}

TestGameObjectCommand::TestGameObjectCommand(GameObject* gameObject) :
	GameObjectCommand(gameObject)
{

}

void TestGameObjectCommand::Execute() const
{

	std::cout << std::format("Test game object command fired, for object at x position {}", m_GameObject->GetWorldTransform().GetPosition().x) << std::endl;
}