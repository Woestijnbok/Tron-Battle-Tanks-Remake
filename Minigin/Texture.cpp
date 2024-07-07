#include <SDL.h>

#include "Texture.h"

Texture::Texture(SDL_Texture* texture) :
	m_Texture{ texture }
{
	
}

Texture::~Texture()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* Texture::GetSDLTexture() const
{
	return m_Texture;
}

glm::ivec2 Texture::GetSize() const
{
	SDL_Rect dst{};
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return glm::ivec2{ dst.w,dst.h };	
}