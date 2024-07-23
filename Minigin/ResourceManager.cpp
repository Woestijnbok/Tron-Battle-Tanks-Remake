#include <stdexcept>
#include <SDL_ttf.h>

#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture.h"
#include "Font.h"

using namespace Minigin;

ResourceManager::ResourceManager() :	
	Singleton<ResourceManager>{},	
	m_TextureRootDirectory{ "../Resources/Textures" },	
	m_FontRootDirectory{ "../Resources/Fonts" }	
{	
	// Checking texture root directory	
	if (std::filesystem::exists(m_TextureRootDirectory))
	{
		if (!std::filesystem::is_directory(m_TextureRootDirectory))
		{
			throw std::runtime_error("ResourceManager::ResourceManager() - texture root directory isn't a directory");
		}
	}
	else throw std::runtime_error("ResourceManager::ResourceManager() - texture root directory doesn't exist");

	// Checking font root directory
	if (std::filesystem::exists(m_FontRootDirectory))
	{
		if (!std::filesystem::is_directory(m_FontRootDirectory))
		{
			throw std::runtime_error("ResourceManager::ResourceManager() - texture root directory isn't a directory");
		}
	}
	else throw std::runtime_error("ResourceManager::ResourceManager() - texture root directory doesn't exist");

	// Initializing ttf support
	if (TTF_Init() == -1)
	{
		throw std::runtime_error(std::string("ResourceManager::ResourceManager() - ") + SDL_GetError());
	}
}

std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::filesystem::path& path) const
{
	const std::filesystem::path fullPath{ m_TextureRootDirectory / path };

	if (std::filesystem::exists(fullPath))
	{
		if (!std::filesystem::is_regular_file(fullPath))
		{
			throw std::runtime_error("ResourceManager::CreateTexture() - path given isn't a regular file");
		}
	}
	else throw std::runtime_error("ResourceManager::CreateTexture() - path given doesn't exist");

	return std::shared_ptr<Texture>(Renderer::GetInstance().CreateTexture(fullPath));		
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::filesystem::path& path, unsigned int size) const	
{
	const std::filesystem::path fullPath{ m_FontRootDirectory / path };	

	if (std::filesystem::exists(fullPath))
	{
		if (!std::filesystem::is_regular_file(fullPath))
		{
			throw std::runtime_error("ResourceManager::CreateFont() - path given isn't a regular file");
		}
	}
	else throw std::runtime_error("ResourceManager::CreateFont() - path given doesn't exist");

	return std::make_shared<Font>(fullPath, size);	
}
