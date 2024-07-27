#include "SpriteComponent.h"
#include "Sprite.h"
#include "Renderer.h"
#include "GameObject.h"

using namespace Minigin;

SpriteComponent::SpriteComponent(GameObject* owner, std::shared_ptr<Sprite> sprite, std::chrono::milliseconds frameTime) :
	Component{ owner },
	m_Sprite{ sprite },
	m_FrameTime{ frameTime },
	m_LastTimePoint{},
	m_Frame{ 0 },
	m_Running{ false }
{

}

SpriteComponent::~SpriteComponent() = default;

void SpriteComponent::Update()
{
	if (!m_Running)
	{
		m_Running = true;
		m_LastTimePoint = std::chrono::steady_clock::now();
	}

	const auto timeDifference{ std::chrono::steady_clock::now() - m_LastTimePoint };			

	if (timeDifference >= m_FrameTime)
	{
		m_LastTimePoint = std::chrono::steady_clock::now();	
		m_Frame = (m_Frame + 1) % m_Sprite->GetFrames();	
	}
}

void SpriteComponent::Render() const		
{
	Renderer::Instance()->RenderSprite(*m_Sprite.get(), m_Frame, GetOwner()->GetWorldTransform());
}

std::shared_ptr<Sprite> SpriteComponent::GetSprite() const
{
	return m_Sprite;	
}

void Minigin::SpriteComponent::Reset()
{
	m_Frame = 0;
}