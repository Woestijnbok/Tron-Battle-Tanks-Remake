#include <SDL_ttf.h>

#include "FPSCounterComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture.h"

FPSCounterComponent::FPSCounterComponent() :
	Component{ nullptr },
	m_Text{ "0.0 FPS" },
	m_Font{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) },
	m_Texture{ nullptr },
	m_LastTimePoint{ std::chrono::high_resolution_clock::now() }
{

}

void FPSCounterComponent::Update(std::chrono::milliseconds deltaTime)
{
	deltaTime;

	// Updating frame rate information
	/*const auto durationCurrentFrame{ std::chrono::high_resolution_clock::now() - m_LastTimePoint };
	const float framesPerSeconds{ 1.0f / std::chrono::duration<float>(durationCurrentFrame).count() };
	std::ostringstream stream{};
	stream << std::fixed << std::setprecision(1) << framesPerSeconds << " FPS";
	m_Text = stream.str();*/

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

	/*m_LastTimePoint = std::chrono::high_resolution_clock::now();*/
}

void FPSCounterComponent::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	++deltaTime;
}

const std::shared_ptr<Texture> FPSCounterComponent::GetTexture() const
{
	return m_Texture;
}

void FPSCounterComponent::SetText(const std::string& text)
{
	m_Text = text;
}