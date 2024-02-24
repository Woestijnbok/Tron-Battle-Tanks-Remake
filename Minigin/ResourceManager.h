#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <string>
#include <memory>

#include "Singleton.h"

class Texture2D;
class Font;

class ResourceManager final : public Singleton<ResourceManager>
{
public:

	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator= (const ResourceManager&) = delete;
	ResourceManager& operator= (const ResourceManager&&) = delete;

	void Init(const std::string& data);
	/*std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;*/
	std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;

private:

	ResourceManager() = default;

	friend class Singleton<ResourceManager>;
	
	std::string m_DataPath;
};

#endif