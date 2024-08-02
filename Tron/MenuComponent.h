#pragma once

#include <set>
#include <string>
#include <vec2.hpp>
#include <imgui.h>

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

	virtual void Render() const override;

private:
	const ImVec2 m_ButtonSize;
	const int m_Spacing;
	const ImVec2 m_WindowSize;	
	const ImVec2 m_StartPosition;

	ImVec2 CalculateWindowSize() const;
	ImVec2 CalculateStartPosition() const;

	void SoloMenuClicked() const;
};