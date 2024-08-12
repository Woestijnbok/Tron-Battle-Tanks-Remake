#pragma once

#include <string>
#include <set>
#include <imgui.h>

#include "Component.h"

class HighscoresComponent final : public Minigin::Component
{
public:
	struct ScoreEntry
	{
		std::string Name;
		int Score;

		explicit operator bool() const;
		bool operator==(const ScoreEntry& rhs) const;
		bool operator<(const ScoreEntry& rhs) const;
		bool operator>(const ScoreEntry& rhs) const;
	};

	explicit HighscoresComponent(Minigin::GameObject* owner);
	virtual ~HighscoresComponent() = default;

	HighscoresComponent(const HighscoresComponent&) = delete;
	HighscoresComponent(HighscoresComponent&&) noexcept = delete;
	HighscoresComponent& operator= (const HighscoresComponent&) = delete;
	HighscoresComponent& operator= (const HighscoresComponent&&) noexcept = delete;

	virtual void Render() const override;

	static void LoadHighscores();
	static void SaveHighscores();
	static void AddScore(const ScoreEntry& score);

private:	
	static const size_t m_MaxScores;
	static std::multiset<ScoreEntry, std::greater<ScoreEntry>> m_ScoreEntries;
	static const ImVec2 m_WindowSize;	
	static const ImVec2 m_StartPosition;

	static ImVec2 CalculateStartPosition();

};