#pragma once

#include <vec2.hpp>

namespace std
{
	namespace filesystem
	{
		class path;
	}
}

struct SDL_Texture;

class Texture final
{
public:

	explicit Texture(const std::filesystem::path& path);
	explicit Texture(SDL_Texture* texture);
	~Texture();

	Texture(const Texture&) = delete;
	Texture(Texture&&) = delete;
	Texture& operator= (const Texture&) = delete;
	Texture& operator= (const Texture&&) = delete;

	SDL_Texture* GetSDLTexture() const;
	glm::ivec2 GetSize() const;

private:

	SDL_Texture* const m_Texture;
};