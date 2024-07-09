#include <filesystem>
#include <SDL_image.h>

#include "Texture.h"
#include "Renderer.h"

using namespace Minigin;

Texture::Texture(const std::filesystem::path& path) :
	m_Texture{ IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), path.generic_string().c_str()) }	
{
	if (m_Texture == nullptr) throw std::runtime_error(std::string("Texture::Texture() - ") + SDL_GetError());
}

Texture::Texture(SDL_Texture* texture) :
	m_Texture{ texture }
{
	if (m_Texture == nullptr) throw std::runtime_error("Texture::Texture() - invalid sdl texture passed");
}

Texture::~Texture()
{
	SDL_DestroyTexture(m_Texture);
}

void Texture::Render(float x, float y) const
{
	Renderer::GetInstance().RenderTexture(*this, x, y);
}

SDL_Texture* Texture::GetSDLTexture() const
{
	return m_Texture;
}

glm::ivec2 Texture::GetSize() const
{
	int width{}, height;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &width, &height);
	return glm::ivec2{ width, height };
}