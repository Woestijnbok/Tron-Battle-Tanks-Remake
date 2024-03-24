#ifndef SCOREBOARD_COMPONENT
#define SCOREBOARD_COMPONENT

#include "Component.h"
#include "TextComponent.h"
#include "EventManager.h"

class ScoreBoardComponent : public Component
{
public:
	ScoreBoardComponent(std::weak_ptr<GameObject> owner, glm::vec2 position);
	virtual ~ScoreBoardComponent();

	ScoreBoardComponent(const ScoreBoardComponent&) = delete;
	ScoreBoardComponent(ScoreBoardComponent&&) = delete;
	ScoreBoardComponent& operator= (const ScoreBoardComponent&) = delete;
	ScoreBoardComponent& operator= (const ScoreBoardComponent&&) = delete;

	virtual void Update(std::chrono::milliseconds deltaTime) override;
	virtual void FixedUpdate(std::chrono::milliseconds deltaTime) override;
	virtual void Render() const override;

	void HandlePlayerDied(const Event& event);
	void HandleScoreChange(const Event& event);

private:
	TextComponent m_Lives;
	TextComponent m_Score;
};

#endif 