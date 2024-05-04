#include <iostream>
#include <format>

#include "CustumCommands.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "Locator.h"

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

PlayerDie::PlayerDie(GameObject* gameObject) :
	GameObjectCommand(gameObject)
{

}

void PlayerDie::Execute(std::chrono::milliseconds deltaTime) const
{
	auto healthComponent = m_GameObject->GetComponent<HealthComponent>();
	if(healthComponent.get())
	{
		healthComponent->Die();
	}

	deltaTime;
}

Add100Score::Add100Score(GameObject* gameObject) :
	GameObjectCommand(gameObject)
{

}

void Add100Score::Execute(std::chrono::milliseconds deltaTime) const
{
	auto scoreComponent = m_GameObject->GetComponent<ScoreComponent>();
	if (scoreComponent.get())
	{
		scoreComponent->AddScore(100);
	}

	deltaTime;
}

void TestMusic1::Execute(std::chrono::milliseconds deltaTime) const
{
	Locator::GetAudio()->PlayMusic("test.mp3");

	deltaTime;
}

void TestMusic2::Execute(std::chrono::milliseconds deltaTime) const
{
	Locator::GetAudio()->PlayMusic("harmony.mp3");

	deltaTime;
}

void TestSoundEffect1::Execute(std::chrono::milliseconds deltaTime) const
{
	Locator::GetAudio()->PlaySound("sweep.wav");

	deltaTime;
}

void TestSoundEffect2::Execute(std::chrono::milliseconds deltaTime) const
{
	Locator::GetAudio()->PlaySound("game over.wav");

	deltaTime;
}

void StopMusic::Execute(std::chrono::milliseconds deltaTime) const
{
	Locator::GetAudio()->StopMusic();

	deltaTime;
}

void StopAll::Execute(std::chrono::milliseconds deltaTime) const
{
	Locator::GetAudio()->StopAll();

	deltaTime;
}