#pragma once

#include <set>
#include <string>
#include <vec2.hpp>
#include <imgui.h>
#include <optional>

#include "Component.h"

class MenuComponent final : public Minigin::Component
{
public:
	explicit MenuComponent(Minigin::GameObject* owner, const glm::ivec2& buttonSize, int spacing);
	virtual ~MenuComponent() = default;	

	MenuComponent(const MenuComponent&) = delete;
	MenuComponent(MenuComponent&&) noexcept = delete;
	MenuComponent& operator= (const MenuComponent&) = delete;
	MenuComponent& operator= (const MenuComponent&&) noexcept = delete;

	std::optional<std::string> GetPlayerName() const;		

	virtual void LateUpdate() override;	
	virtual void Render() const override;

private:
	const ImVec2 m_ButtonSize;
	const int m_Spacing;
	const ImVec2 m_WindowSize;	
	const ImVec2 m_MenuStartPosition;
	const std::string m_DefaultPlayerName;
	std::string m_PlayerName;
	const int m_NameBarWidth;
	const int m_NameBarOffset;
	const ImVec2 m_NameStartPosition;

	ImVec2 CalculateMenuStartPosition() const;
	ImVec2 CalculateNameStartPosition();
	void SoloMenuClicked() const;
	void CoopMenuClicked() const;
	void VersusMenuClicked() const;
	void ScoreboardMenuClicked() const;

};