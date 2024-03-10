#include <SDL_ttf.h>

#include "FPSCounterComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture.h"
#include "GameObject.h"

FPSCounterComponent::FPSCounterComponent(std::weak_ptr<GameObject> owner) :
	Component{ owner },
	m_Text{ "0.0 FPS" },
	m_Font{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) },
	m_Texture{ nullptr },
	m_LastTimePoint{ std::chrono::high_resolution_clock::now() },
	m_FrameCounter{ 0 }
{

}

void FPSCounterComponent::Update(std::chrono::milliseconds deltaTime)
{
	deltaTime;

	++m_FrameCounter;
	const auto currentTime{ std::chrono::high_resolution_clock::now() };
	const auto timeDifference{ std::chrono::high_resolution_clock::now() - m_LastTimePoint };

	if (timeDifference >= std::chrono::seconds(1))
	{
		std::ostringstream stream{};
		stream << m_FrameCounter << " FPS";
		m_Text = stream.str();

		// Updating the SDL texture
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture>(texture);

		m_FrameCounter = 0;
		m_LastTimePoint = currentTime;
	}
}

void FPSCounterComponent::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	++deltaTime;
}

void FPSCounterComponent::Render() const
{
	std::shared_ptr<GameObject> owner = m_Owner.lock();
	if ((owner != nullptr) and (m_Texture.get() != nullptr))
	{
		auto position{ owner->GetWorldTransform().GetPosition() };
		Renderer::GetInstance().RenderTexture(*m_Texture.get(), position.x, position.y);
	}
}

const std::shared_ptr<Texture> FPSCounterComponent::GetTexture() const
{
	return m_Texture;
}

void FPSCounterComponent::SetText(const std::string& text)
{
	m_Text = text;
}