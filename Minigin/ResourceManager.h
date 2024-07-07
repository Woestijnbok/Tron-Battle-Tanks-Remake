#pragma once

#include <string>
#include <memory>

#include "Singleton.h"

class Texture;
class Font;

class ResourceManager final : public Singleton<ResourceManager>
{
public:

	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator= (const ResourceManager&) = delete;
	ResourceManager& operator= (const ResourceManager&&) = delete;

	void Init();
	std::shared_ptr<Texture> LoadTexture(const std::string& file) const;
	std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;

private:

	ResourceManager() = default;

	friend class Singleton<ResourceManager>;
};