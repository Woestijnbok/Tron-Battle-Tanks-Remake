#include <SDL.h>

#include "Texture2D.h"

Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

void Texture2D::Update(std::chrono::milliseconds deltaTime)
{
	++deltaTime;
}

void Texture2D::FixedUpdate(std::chrono::milliseconds deltaTime)
{
	++deltaTime;
}

glm::ivec2 Texture2D::GetSize() const
{
	SDL_Rect dst{};
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

Texture2D::Texture2D(std::shared_ptr<GameObject> owner, SDL_Texture* texture) :
	Component{ owner }
{
	m_Texture = texture;
}