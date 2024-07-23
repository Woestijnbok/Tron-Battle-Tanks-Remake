#pragma once

#include <vec2.hpp>

struct SDL_Texture;

namespace Minigin
{
	class Transform;

	class Texture final
	{
	public:
		explicit Texture(SDL_Texture* texture);	
		~Texture();

		Texture(const Texture&) = delete;
		Texture(Texture&&) noexcept = delete;
		Texture& operator= (const Texture&) = delete;
		Texture& operator= (const Texture&&) noexcept = delete;

		void Render(const Transform& transform) const;
		SDL_Texture* GetTexture() const;	
		glm::ivec2 GetSize() const;

	private:
		SDL_Texture* const m_Texture;

	};
}