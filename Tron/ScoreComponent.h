#ifndef SCORE_COMPONENT
#define SCORE_COMPONENT

#include "Component.h"

class ScoreComponent final : public Component
{
public:
	ScoreComponent(std::weak_ptr<GameObject> owner);
	virtual ~ScoreComponent() = default;

	ScoreComponent(const ScoreComponent&) = delete;
	ScoreComponent(ScoreComponent&&) = delete;
	ScoreComponent& operator= (const ScoreComponent&) = delete;
	ScoreComponent& operator= (const ScoreComponent&&) = delete;

	virtual void Update(std::chrono::milliseconds deltaTime) override;
	virtual void FixedUpdate(std::chrono::milliseconds deltaTime) override;

	void AddScore(int amount);
	int GetScore() const;

private:
	int m_Score;

};

#endif