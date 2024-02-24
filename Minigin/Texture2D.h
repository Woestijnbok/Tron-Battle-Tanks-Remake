#ifndef TEXTURE2D
#define TEXTURE2D

#include <glm/vec2.hpp>

#include "Component.h"
#include "GameObject.h"

struct SDL_Texture;

class Texture2D final : public Component
{
public:

	explicit Texture2D(std::shared_ptr<GameObject> owner, SDL_Texture* texture);
	~Texture2D();

	Texture2D(const Texture2D&) = delete;
	Texture2D(Texture2D&&) = delete;
	Texture2D& operator= (const Texture2D&) = delete;
	Texture2D& operator= (const Texture2D&&) = delete;

	virtual void Update(std::chrono::milliseconds deltaTime) override;
	virtual void FixedUpdate(std::chrono::milliseconds deltaTime) override;

	SDL_Texture* GetSDLTexture() const;
	glm::ivec2 GetSize() const;

private:

	SDL_Texture* m_Texture;
};

#endif