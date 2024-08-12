#pragma once

#include <memory>

#include "Component.h"
#include "Text.h"
#include "Texture.h"

class ScoreboardComponent final : public Minigin::Component
{
public:
	explicit ScoreboardComponent(Minigin::GameObject* owner, int score, int lives, bool withScore = true);
	virtual ~ScoreboardComponent() = default;

	ScoreboardComponent(const ScoreboardComponent&) = delete;
	ScoreboardComponent(ScoreboardComponent&&) noexcept = delete;
	ScoreboardComponent& operator= (const ScoreboardComponent&) = delete;
	ScoreboardComponent& operator= (const ScoreboardComponent&&) noexcept = delete;

	void UpdateScore(int score);
	void UpdateLives(int lives);
	int GetScore() const;
	int GetLives() const;

	virtual void Render() const;

private:
	std::unique_ptr<Minigin::Text> m_ScoreText;	
	std::shared_ptr<Minigin::Texture> m_LiveTexture;
	int m_Score;
	int m_Lives;
	const bool m_WithScore;

	static const int m_LiveSize;
	static const int m_LivesOffset;
	static const int m_ScoreLivesOffset;
};