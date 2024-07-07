#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture.h"
#include "Font.h"

void ResourceManager::Init()
{
	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::string& file) const
{
	const std::string filePath{ "../Resources/Textures/" + file };

	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), filePath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture>(texture);
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	const std::string filePath{ "../Resources/Fonts/" + file };

	return std::make_shared<Font>(filePath, size);
}
