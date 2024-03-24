#include <format>

#include "ScoreBoardComponent.h"
#include "HealthComponent.h"
#include "EventManager.h"
#include "ResourceManager.h"

ScoreBoardComponent::ScoreBoardComponent(std::weak_ptr<GameObject> owner) :
	Component{ owner },
	m_Lives{ owner, "# lives 10: ", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20) },
	m_Score{ owner, "", ResourceManager::GetInstance().LoadFont("Lingua.otf", 20) }
{
	EventManager::GetInstance().AddHandler(EventType::PlayerDied,
		std::bind(&ScoreBoardComponent::HandlePlayerDied, this, std::placeholders::_1)
	);
}

void ScoreBoardComponent::Update(std::chrono::milliseconds deltaTime)
{
	m_Lives.Update(deltaTime);
}

void ScoreBoardComponent::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	deltaTime;
}

void ScoreBoardComponent::Render() const
{
	m_Lives.Render();
}

void ScoreBoardComponent::HandlePlayerDied(const Event& event)
{
	m_Lives.SetText(std::format("# lives: {}", event.GetNumberArguments().at(0)));
}