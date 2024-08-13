#include <filesystem>
#include <regex>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <iostream>

#include "ResourceManager.h"
#include "Engine.h"

#include "HighscoresComponent.h"

HighscoresComponent::ScoreEntry::operator bool() const	
{
	const std::regex pattern{ "^[A-Za-z]+$" };	

	return std::regex_match(Name, pattern) and Score >= 0;
}

bool HighscoresComponent::ScoreEntry::operator==(const ScoreEntry& rhs) const
{
	return Name == rhs.Name and Score == rhs.Score;
}

bool HighscoresComponent::ScoreEntry::operator<(const ScoreEntry& rhs) const
{
	if (Score == rhs.Score)
	{
		return Name > rhs.Name;
	}
	else
	{
		return Score < rhs.Score;	
	}	
}

bool HighscoresComponent::ScoreEntry::operator>(const ScoreEntry& rhs) const
{
	if (Score == rhs.Score)
	{
		return Name < rhs.Name;
	}
	else
	{
		return Score > rhs.Score;
	}
}

const size_t HighscoresComponent::m_MaxScores{ 10 };

std::multiset<HighscoresComponent::ScoreEntry, std::greater<HighscoresComponent::ScoreEntry>> HighscoresComponent::m_ScoreEntries{};

const ImVec2 HighscoresComponent::m_WindowSize{ 300.0f, 300.0f };	

const ImVec2 HighscoresComponent::m_StartPosition{ CalculateStartPosition() };	

HighscoresComponent::HighscoresComponent(Minigin::GameObject* owner) :
	Component{ owner }	
{
	
}

void HighscoresComponent::SaveHighscores()
{
	const std::filesystem::path fullPath{ Minigin::ResourceManager::Instance()->GetFileRootPath() / "Scores.csv" };		

	std::ofstream file{ fullPath };		

	file << "Name, Score";

	if(!m_ScoreEntries.empty())	
	{
		file << std::endl;	

		size_t index{};
		for (const ScoreEntry& scoreEntry : m_ScoreEntries)		
		{
			file << scoreEntry.Name << ", " << scoreEntry.Score;		

			if (index < m_ScoreEntries.size() - 1)	
			{
				file << std::endl;	
			}

			++index;	
		}
	}
}

void HighscoresComponent::Render() const	
{
	ImGui::SetNextWindowPos(m_StartPosition);	
	ImGui::SetNextWindowSize(m_WindowSize);
	ImGui::Begin("Table Example", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove);	

	// Define the number of columns
	const int numColumns = 2;

	// Create a table with the specified number of columns
	ImGui::BeginTable("Highscores", numColumns, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg);

	// Define column headers
	ImGui::TableSetupColumn("Name");  // Column for strings
	ImGui::TableSetupColumn("Score");     // Column for integers

	// Define the table header row
	ImGui::TableHeadersRow();

	// Iterate through the rows of data
	for (const ScoreEntry& scoreEntry : m_ScoreEntries) 
	{	
		// Start a new row
		ImGui::TableNextRow();	

		// Start a new cell for the string column
		ImGui::TableSetColumnIndex(0);	
		ImGui::Text("%s", scoreEntry.Name.c_str());	

		// Start a new cell for the integer column
		ImGui::TableSetColumnIndex(1);	
		ImGui::Text("%d", scoreEntry.Score);			
	}	

	// End the table
	ImGui::EndTable();	

	// End the ImGui window
	ImGui::End();	
}

void HighscoresComponent::LoadHighscores()
{
	const std::filesystem::path fullPath{ Minigin::ResourceManager::Instance()->GetFileRootPath() / "Scores.csv" };	

	if (std::filesystem::exists(fullPath))	
	{
		if (!std::filesystem::is_regular_file(fullPath))	
		{
			throw std::runtime_error("HighscoresComponent::LoadScores() - Scores.csv is corrupt");	
		}
	}
	else
	{
		std::ofstream scores{ fullPath };

		if (!scores.is_open() or !scores.good())
		{
			throw std::runtime_error("HighscoresComponent::LoadScores() - Failed creating Scores.csv");
		}
		else
		{
			scores << "Name, Score";
		}
	}

	std::ifstream file{ fullPath };
	std::string line{};
	const std::regex pattern{ R"(^([^,]+), (\d+)$)" };	

	// Skip header line
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::smatch match{};
		if (std::regex_match(line, match, pattern))		
		{
			AddScore(ScoreEntry{ match[1].str(), std::stoi(match[2].str()) });		
		}	
	}
}

void HighscoresComponent::AddScore(const ScoreEntry& score)
{
	if (score)
	{
		m_ScoreEntries.insert(score);

		if (m_ScoreEntries.size() > m_MaxScores)
		{
			auto begin{ m_ScoreEntries.begin() };
			std::advance(begin, m_MaxScores);
			
			m_ScoreEntries.erase(begin, m_ScoreEntries.end());
		}
	}
}

ImVec2 HighscoresComponent::CalculateStartPosition()
{
	ImVec2 startPosition{};

	const ImVec2 centerWindow{ float(Minigin::Engine::GetWindowSize().x) * 0.5f , float(Minigin::Engine::GetWindowSize().y) * 0.5f };

	startPosition.x = centerWindow.x - (m_WindowSize.x / 2);
	startPosition.y = centerWindow.y - (m_WindowSize.y / 2);

	return startPosition;
}
