#include "HealthComponent.h"
#include "EventManager.h"

HealthComponent::HealthComponent(std::weak_ptr<GameObject> owner) :
	Component{ owner },
	m_Lives{ 10 }
{

}

void HealthComponent::Update(std::chrono::milliseconds deltaTime)
{
	deltaTime;
}

void HealthComponent::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	deltaTime;
}

void HealthComponent::Die()
{
	if (m_Lives > 0)
	{
		--m_Lives;
		Event event{ EventType::PlayerDied, this };
		event.AddArgument(m_Lives);
		EventManager::GetInstance().SendEvent(event);
	}
}

unsigned int HealthComponent::GetLives() const
{
	return m_Lives;
}