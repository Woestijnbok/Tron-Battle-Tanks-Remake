#include <SDL.h>

#include "MenuComponent.h"
#include "Engine.h"
#include "SceneManager.h"

using namespace Minigin;

MenuComponent::MenuComponent(Minigin::GameObject* owner, const glm::ivec2& buttonSize, int spacing) :
	Component{ owner },
    m_ButtonSize{ float(buttonSize.x), float(buttonSize.y) },   
    m_Spacing{ spacing },
    m_WindowSize{ CalculateWindowSize() },
    m_StartPosition{ CalculateStartPosition() }
{   
    
}

void MenuComponent::Render() const
{
    ImGui::SetNextWindowPos(ImVec2{ 0.0f, 0.0f});
    ImGui::SetNextWindowSize(m_WindowSize);   
    ImGui::Begin("Invisible Window", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove);     

    ImGui::SetCursorPos(m_StartPosition);
    if (ImGui::Button("Solo", m_ButtonSize))    
    {
        this->SoloMenuClicked();
    }

    ImGui::SetCursorPos(ImVec2{ m_StartPosition.x, m_StartPosition.y + (m_ButtonSize.y + m_Spacing) * 1 });
    if (ImGui::Button("Coop", m_ButtonSize))    
    {
        // Action for Load Game
    }

    ImGui::SetCursorPos(ImVec2{ m_StartPosition.x, m_StartPosition.y + (m_ButtonSize.y + m_Spacing) * 2 }); 
    if (ImGui::Button("Versus", m_ButtonSize))  
    {
        // Action for Settings
    }

    ImGui::SetCursorPos(ImVec2{ m_StartPosition.x, m_StartPosition.y + (m_ButtonSize.y + m_Spacing) * 3 });
    if (ImGui::Button("Scoreboard", m_ButtonSize))  
    {
        // Action for Exit
    }

    ImGui::End();
}   

ImVec2 MenuComponent::CalculateWindowSize() const
{
    int width{}, height{};
    SDL_GetWindowSize(Engine::GetWindow(), &width, &height);

    return ImVec2{ float(width), float(height) };
}

ImVec2 MenuComponent::CalculateStartPosition() const    
{
    const ImVec2 windowCenter{ m_WindowSize.x * 0.5f, m_WindowSize.y * 0.5f };         
    const float totalHeight{ (m_ButtonSize.y + m_Spacing) * 4 - m_Spacing};

    return ImVec2{ windowCenter.x - (m_ButtonSize.x * 0.5f), windowCenter.y - (totalHeight * 0.5f) };      
}

void MenuComponent::SoloMenuClicked() const
{
    SceneManager::Instance()->GetScene("Main Menu")->SetStatus(ControllableObject::Status::Disabled);
    SceneManager::Instance()->GetScene("First Level")->SetStatus(ControllableObject::Status::Enabled);
}