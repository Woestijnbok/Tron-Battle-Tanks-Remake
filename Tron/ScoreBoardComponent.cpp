#include <format>

#include "ScoreBoardComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "EventManager.h"
#include "ResourceManager.h"

ScoreBoardComponent::ScoreBoardComponent(std::weak_ptr<GameObject> owner, glm::vec2 position) :
	Component{ owner },
	m_Lives{ owner, std::format("# lives: {}", owner.lock()->GetComponent<HealthComponent>()->GetLives()), ResourceManager::GetInstance().LoadFont("Lingua.otf", 20), position},
	m_Score{ owner, std::format("Score: {}", owner.lock()->GetComponent<ScoreComponent>()->GetScore()), ResourceManager::GetInstance().LoadFont("Lingua.otf", 20), glm::vec2{ position.x, position.y + 30.0f } }
{
	EventManager::GetInstance().AddHandler(EventType::PlayerDied,
		std::bind(&ScoreBoardComponent::HandlePlayerDied, this, std::placeholders::_1)
	);

	EventManager::GetInstance().AddHandler(EventType::ScoreUpdated,
		std::bind(&ScoreBoardComponent::HandleScoreChange, this, std::placeholders::_1)
	);
}

ScoreBoardComponent::~ScoreBoardComponent()
{
	EventManager::GetInstance().RemoveHandler(EventType::PlayerDied,
		std::bind(&ScoreBoardComponent::HandlePlayerDied, this, std::placeholders::_1)
	);

	EventManager::GetInstance().RemoveHandler(EventType::ScoreUpdated,
		std::bind(&ScoreBoardComponent::HandleScoreChange, this, std::placeholders::_1)
	);
}

void ScoreBoardComponent::Update(std::chrono::milliseconds deltaTime)
{
	m_Lives.Update(deltaTime);
	m_Score.Update(deltaTime);
}

void ScoreBoardComponent::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	deltaTime;
}

void ScoreBoardComponent::Render() const
{
	m_Lives.Render();
	m_Score.Render();
}

void ScoreBoardComponent::HandlePlayerDied(const Event& event)
{
	if (event.GetCaller() != m_Owner.lock()->GetComponent<HealthComponent>().get()) return;

	m_Lives.SetText(std::format("# lives: {}", event.GetNumberArguments().at(0)));
}

void ScoreBoardComponent::HandleScoreChange(const Event& event)
{
	if (event.GetCaller() != m_Owner.lock()->GetComponent<ScoreComponent>().get()) return;

	m_Score.SetText(std::format("Score: {}", event.GetNumberArguments().at(0)));
}