#include <iostream>
#include <format>

#include "CustumCommands.h"
#include "GameObject.h"

void TestCommand::Execute(std::chrono::milliseconds deltaTime) const
{
	deltaTime;
	std::cout << "Test command fired" << std::endl;
}

TestGameObjectCommand::TestGameObjectCommand(GameObject* gameObject) :
	GameObjectCommand(gameObject)
{

}

void TestGameObjectCommand::Execute(std::chrono::milliseconds deltaTime) const
{
	deltaTime;
	std::cout << std::format("Test game object command fired, for object at x position {}", m_GameObject->GetWorldTransform().GetPosition().x) << std::endl;
}

MoveRight::MoveRight(GameObject* gameObject) :
	GameObjectCommand(gameObject)
{

}

void MoveRight::Execute(std::chrono::milliseconds deltaTime) const
{
	auto transform{ m_GameObject->GetLocalTransform() };
	float seconds{ std::chrono::duration_cast<std::chrono::duration<float>>(deltaTime).count() };
	m_GameObject->SetLocalPosition(transform.GetPosition().x + (100.0f * seconds), transform.GetPosition().y);
}

MoveLeft::MoveLeft(GameObject* gameObject) :
	GameObjectCommand(gameObject)
{

}

void MoveLeft::Execute(std::chrono::milliseconds deltaTime) const
{
	auto transform{ m_GameObject->GetLocalTransform() };
	float seconds{ std::chrono::duration_cast<std::chrono::duration<float>>(deltaTime).count() };
	m_GameObject->SetLocalPosition(transform.GetPosition().x - (100.0f * seconds), transform.GetPosition().y);
}

MoveUp::MoveUp(GameObject* gameObject) :
	GameObjectCommand(gameObject)
{

}

void MoveUp::Execute(std::chrono::milliseconds deltaTime) const
{
	auto transform{ m_GameObject->GetLocalTransform() };
	float seconds{ std::chrono::duration_cast<std::chrono::duration<float>>(deltaTime).count() };
	m_GameObject->SetLocalPosition(transform.GetPosition().x, transform.GetPosition().y - (100.0f * seconds));
}

MoveDown::MoveDown(GameObject* gameObject) :
	GameObjectCommand(gameObject)
{

}

void MoveDown::Execute(std::chrono::milliseconds deltaTime) const
{
	auto transform{ m_GameObject->GetLocalTransform() };
	float seconds{ std::chrono::duration_cast<std::chrono::duration<float>>(deltaTime).count() };
	m_GameObject->SetLocalPosition(transform.GetPosition().x, transform.GetPosition().y + (100.0f * seconds));
}