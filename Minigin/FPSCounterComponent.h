#pragma once

#include <chrono>
#include <memory>

#include "Component.h"

namespace Minigin
{
	class TextComponent;

	class FPSCounterComponent final : public Component
	{
	public:

		FPSCounterComponent(GameObject* owner);
		~FPSCounterComponent() = default;

		FPSCounterComponent(const FPSCounterComponent&) = delete;
		FPSCounterComponent(FPSCounterComponent&&) = delete;
		FPSCounterComponent& operator= (const FPSCounterComponent&) = delete;
		FPSCounterComponent& operator= (const FPSCounterComponent&&) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		TextComponent* GetTextComponent() const;

	private:

		std::unique_ptr<TextComponent> m_TextComponent;
		std::chrono::steady_clock::time_point m_LastTimePoint;
		unsigned int m_FrameCounter;
	};
}