#include <SDL.h>

#include "MenuComponent.h"
#include "Engine.h"
#include "SceneManager.h"
#include "Loaders.h"
#include "HighscoresComponent.h"

using namespace Minigin;

MenuComponent::MenuComponent(Minigin::GameObject* owner, const glm::ivec2& buttonSize, int spacing) :
	Component{ owner },
    m_ButtonSize{ float(buttonSize.x), float(buttonSize.y) },   
    m_Spacing{ spacing },
    m_WindowSize{ static_cast<float>(Engine::GetWindowSize().x), static_cast<float>(Engine::GetWindowSize().y) },
    m_MenuStartPosition{ CalculateMenuStartPosition() },
    m_DefaultPlayerName{ "Name only characters..." },
    m_PlayerName{ m_DefaultPlayerName },
    m_NameBarWidth{ 200 },
    m_NameBarOffset{ 100 },
    m_NameStartPosition{ CalculateNameStartPosition() }
{   
   
}

std::optional<std::string> MenuComponent::GetPlayerName() const  
{ 
    if (m_PlayerName != m_DefaultPlayerName)
    {   
        const std::string newName{ m_PlayerName.substr(0, m_PlayerName.find('\0')) };   

        if (HighscoresComponent::ScoreEntry{ newName, 0 })      
        {
            return newName;
        }   
    }

    return std::nullopt;
}

void MenuComponent::LateUpdate()
{
    if (m_PlayerName != m_DefaultPlayerName)
    {
        const std::string newName{ m_PlayerName.substr(0, m_PlayerName.find('\0')) };

        if (!HighscoresComponent::ScoreEntry{ newName, 0 }) 
        {
            m_PlayerName = m_DefaultPlayerName;
        }
    }
}

void MenuComponent::Render() const
{
    ImGui::SetNextWindowPos(ImVec2{ 0.0f, 0.0f });  
    ImGui::SetNextWindowSize(m_WindowSize); 
    ImGui::Begin("Invisible Window", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove);    

    ImGui::SetNextItemWidth(static_cast<float>(m_NameBarWidth));
    ImGui::SetCursorPos(m_NameStartPosition);
    ImGui::InputText("##PlayerName", const_cast<char*>(m_PlayerName.data()), m_PlayerName.size() + 1, ImGuiInputTextFlags_::ImGuiInputTextFlags_AutoSelectAll);

    ImGui::SetCursorPos(m_MenuStartPosition);   
    if (ImGui::Button("Solo", m_ButtonSize))    
    {
        this->SoloMenuClicked();    
    }

    ImGui::SetCursorPos(ImVec2{ m_MenuStartPosition.x, m_MenuStartPosition.y + (m_ButtonSize.y + m_Spacing) * 1 }); 
    if (ImGui::Button("Coop", m_ButtonSize))
    {       
        this->CoopMenuClicked();    
    }

    ImGui::SetCursorPos(ImVec2{ m_MenuStartPosition.x, m_MenuStartPosition.y + (m_ButtonSize.y + m_Spacing) * 2 }); 
    if (ImGui::Button("Versus", m_ButtonSize))
    {
        this->VersusMenuClicked();  
    }

    ImGui::SetCursorPos(ImVec2{ m_MenuStartPosition.x, m_MenuStartPosition.y + (m_ButtonSize.y + m_Spacing) * 3 }); 
    if (ImGui::Button("Scoreboard", m_ButtonSize))
    {
        this->ScoreboardMenuClicked();  
    }

    ImGui::End();   
}

ImVec2 MenuComponent::CalculateMenuStartPosition() const    
{
    const ImVec2 windowCenter{ m_WindowSize.x * 0.5f, m_WindowSize.y * 0.5f };         
    const float totalHeight{ (m_ButtonSize.y + m_Spacing) * 4 - m_Spacing};

    return ImVec2{ windowCenter.x - (m_ButtonSize.x * 0.5f), windowCenter.y - (totalHeight * 0.5f) };      
}

ImVec2 MenuComponent::CalculateNameStartPosition()
{
    ImVec2 nameStart{};

    const ImVec2 windowCenter{ m_WindowSize.x * 0.5f, m_WindowSize.y * 0.5f };
    
    nameStart.x = windowCenter.x - (m_NameBarWidth * 0.5f);
    nameStart.y = static_cast<float>(m_NameBarOffset);

    return nameStart;
}

void MenuComponent::SoloMenuClicked() const
{
    LoadLevelOne(); 
}

void MenuComponent::CoopMenuClicked() const
{
    LoadCoopLevel();
}

void MenuComponent::VersusMenuClicked() const
{
    LoadVersusLevel();
}

void MenuComponent::ScoreboardMenuClicked() const
{
    LoadScoreboard();
}