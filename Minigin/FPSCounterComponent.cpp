#include <SDL_ttf.h>

#include "FPSCounterComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"

FPSCounterComponent::FPSCounterComponent(GameObject* owner) :
	Component{ owner },
	m_TextComponent{ new TextComponent{ owner, "0.0 FPS", ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) } },
	m_LastTimePoint{ std::chrono::high_resolution_clock::now() },
	m_FrameCounter{ 0 }
{

}

FPSCounterComponent::~FPSCounterComponent()
{
	delete m_TextComponent;
}

void FPSCounterComponent::Update()
{
	++m_FrameCounter;
	const auto timeDifference{ std::chrono::high_resolution_clock::now() - m_LastTimePoint };

	if (timeDifference >= std::chrono::seconds(1))
	{
		std::ostringstream stream{};
		stream << m_FrameCounter << " FPS";
		m_TextComponent->SetText(stream.str());

		m_TextComponent->Update();

		m_FrameCounter = 0;
		m_LastTimePoint = std::chrono::high_resolution_clock::now();	
	}
}

void FPSCounterComponent::Render() const
{
	m_TextComponent->Render();	
}

TextComponent* FPSCounterComponent::GetTextComponent() const
{
	return m_TextComponent;
}