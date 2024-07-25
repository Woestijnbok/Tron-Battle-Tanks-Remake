#include "FPSCounterComponent.h"
#include "Text.h"
#include "GameObject.h"
#include "ResourceManager.h"

using namespace Minigin;

FPSCounterComponent::FPSCounterComponent(GameObject* owner) :
	Component{ owner },
	m_LastTimePoint{ std::chrono::high_resolution_clock::now() },
	m_FrameCounter{ 0 },
	m_Text{ std::make_unique<Text>("0.0 FPS", ResourceManager::Instance()->LoadFont("Lingua.otf", 36)) }		
{
	
}

FPSCounterComponent::~FPSCounterComponent() = default;

void FPSCounterComponent::Update()
{
	++m_FrameCounter;
	const auto timeDifference{ std::chrono::high_resolution_clock::now() - m_LastTimePoint };

	if (timeDifference >= std::chrono::seconds(1))
	{
		std::ostringstream stream{};
		stream << m_FrameCounter << " FPS";
		m_Text->SetText(stream.str());		

		m_FrameCounter = 0;
		m_LastTimePoint = std::chrono::high_resolution_clock::now();
	}

	m_Text->Update();	
}

void FPSCounterComponent::Render() const
{
	m_Text->Render(GetOwner()->GetWorldTransform());
}