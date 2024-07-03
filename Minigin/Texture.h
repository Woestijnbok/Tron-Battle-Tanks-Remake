#ifndef TEXTURE2D
#define TEXTURE2D

#include <vec2.hpp>

struct SDL_Texture;

class Texture final
{
public:

	explicit Texture(SDL_Texture* texture);
	virtual ~Texture();

	Texture(const Texture&) = delete;
	Texture(Texture&&) = delete;
	Texture& operator= (const Texture&) = delete;
	Texture& operator= (const Texture&&) = delete;

	SDL_Texture* GetSDLTexture() const;
	glm::ivec2 GetSize() const;

protected:

	SDL_Texture* m_Texture;
};

#endif