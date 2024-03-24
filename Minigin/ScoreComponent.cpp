#include "ScoreComponent.h"
#include "EventManager.h"

ScoreComponent::ScoreComponent(std::weak_ptr<GameObject> owner) :
	Component{ owner },
	m_Score{ 0 }
{

}

void ScoreComponent::Update(std::chrono::milliseconds deltaTime)
{
	deltaTime;
}

void ScoreComponent::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	deltaTime;
}

void ScoreComponent::AddScore(int amount)
{
	m_Score += amount;
	Event event{ EventType::ScoreUpdated, this };
	event.AddArgument(m_Score);
	EventManager::GetInstance().SendEvent(event);
}

int ScoreComponent::GetScore() const
{
	return m_Score;
}